#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "event.h"
#include "../dat.h"
#include "../fns.h"

const int maxstreamsize = 1e6;

__global__ void
k_sum(int n, int offset, uint *a, uint *b, uint *c) {
	int i = offset + blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	size_t size;
	uint *da, *db, *dc, i, todo, doing;
	int thd, blk, nstreams, offset;
	Event *e;
	cudaStream_t *streams;
	uint *streamsize;

	e = newevent();

	size = n*sizeof(uint);
	cudaMalloc(&da, size);
	cudaMalloc(&db, size);
	cudaMalloc(&dc, size);

	nstreams = (n+maxstreamsize-1)/maxstreamsize;
	streams = (cudaStream_t*) malloc(sizeof(cudaStream_t)*nstreams);
	streamsize = (uint*) malloc(sizeof(uint)*nstreams);

	todo = n;
	for(i = 0; i < nstreams; i++) {
		cudaStreamCreate(&streams[i]);
		if(todo < maxstreamsize)
			doing = todo;
		else
			doing = maxstreamsize;

		todo -= doing;
		streamsize[i] = doing;
	}

	thd = 32;
	blk = (n+thd-1)/thd;

	fprintf(stderr, "running with %d streams\n", nstreams);
	for(i = 0, offset = 0; i < nstreams; offset += streamsize[i], i++) {
		size = streamsize[i]*sizeof(uint);
		fprintf(stderr, "i: %d, size: %u, offset: %u\n", i, size, offset);

		start(e, streams[i]);
		cudaMemcpyAsync(&da[offset], &a[offset], size, cudaMemcpyHostToDevice, streams[i]);
		cudaMemcpyAsync(&db[offset], &b[offset], size, cudaMemcpyHostToDevice, streams[i]);
		addmsr(lp, newmsr(UnitMS, "cudaMemcpyHtD", stop(e, streams[i])));

		start(e, streams[i]);
		k_sum<<<blk, thd, 0, streams[i]>>>(n, offset, da, db, dc);
		addmsr(lp, newmsr(UnitMS, "k_sum", stop(e, streams[i])));

		start(e, streams[i]);
		cudaMemcpyAsync(&c[offset], &dc[offset], size, cudaMemcpyDeviceToHost, streams[i]);
		addmsr(lp, newmsr(UnitMS, "cudaMemcpyDtH", stop(e, streams[i])));
	}

	for(i = 0; i < nstreams; i++) {
		cudaStreamSynchronize(streams[i]);
		cudaStreamDestroy(streams[i]);
	}

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	freeevent(e);
	free(streams);
	free(streamsize);
}
