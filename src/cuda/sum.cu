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
sum(Msr *m, int n, uint a[], uint b[], uint c[]) {
	uint *da, *db, *dc;
	size_t s;
	int thd, blk;

	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);

	thd = 32;
	blk = (n+thd-1)/thd;

	fprintf(stderr, "blk: %d, thd: %d\n", blk, thd);
	k_sum<<<blk, thd>>>(n, da, db, dc);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}
