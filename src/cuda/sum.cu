#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "../dat.h"
#include "../fns.h"

__global__ void
k_sum(int n, uint *a, uint *b, uint *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	size_t s;
	uint *da, *db, *dc;
	int thd, blk;
	cudaEvent_t start, stop;
	float elaps;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	cudaEventRecord(start, 0);
	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elaps, start, stop);
	addmsr(lp, newmsr(UnitMS, "cudaMemcpyHtD", elaps));

	thd = 32;
	blk = (n+thd-1)/thd;

	cudaEventRecord(start, 0);
	k_sum<<<blk, thd>>>(n, da, db, dc);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elaps, start, stop);
	addmsr(lp, newmsr(UnitMS, "k_sum", elaps));

	cudaEventRecord(start, 0);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elaps, start, stop);
	addmsr(lp, newmsr(UnitMS, "cudaMemcpyDtH", elaps));

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}
