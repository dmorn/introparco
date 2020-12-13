#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "event.h"
#include "../dat.h"
#include "../fns.h"

const int maxstreamsize = 1e6

__global__ void
k_sum(int n, uint *a, uint *b, uint *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	size_t size;
	uint *da, *db, *dc, i, offset;
	int thd, blk, nstreams, nbytes, streamsize;
	Event *e;
	cudaStream_t *streams;

	e = newevent();

	size = n*sizeof(uint);
	streamsize = (maxstreamsize < n) ? maxstreamsize : n;
	nstreams = n / streamsize;
	nbytes = n / nstreams;
	streams = malloc(sizeof(cudaStream_t)*nstreams);
	for(i = 0; i < nstreams; i++) {
		cudaStreamCreate(streams[i]);
	}

	thd = 32;
	blk = (n+thd-1)/thd;

	cudaMalloc(&da, size);
	cudaMalloc(&db, size);
	cudaMalloc(&dc, size);

	for(i = 0; i < nstreams; i++) {
		offset = i * streamsize;
		start(e, *streams[i]);
		cudaMemcpyAsync(da[offset], a[offset], streamsize, cudaMemcpyHostToDevice, stream);
		addmsr(lp, newmsr(UnitMS, "cudaMemcpyHtD", stop(e, *stream[i])));

		start(e, *stream[i]);
		k_sum<<<blk, thd, 0, *streams[i]>>>(streamsize, da[offset], db[offset], dc[offset]);
		addmsr(lp, newmsr(UnitMS, "k_sum", stop(e, *streams[i])));

		start(e, *stream[i]);
		cudaMemcpyAsync(c[offset], dc[offset], streamsize, cudaMemcpyDeviceToHost, *stream[i]);
		addmsr(lp, newmsr(UnitMS, "cudaMemcpyDtH", stop(e, *streams[i])));
	}

	for(i = 0; i < nstreams; i++) {
		cudaStreamSynchronize(*streams[i]);
		cudaStreamDestroy(*streams[i]);
	}

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	cudaStreamDestroy(stream);
	freeevent(e);
	free(streams);
}
