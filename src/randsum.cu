#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <cuda.h>
#include "randsum.h"

__global__
void k_randsum(int n, uint32_t *a, uint32_t *b, uint32_t *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

extern "C" void randsum(int n, uint32_t *a, uint32_t *b, uint32_t *c) {
	uint32_t *da, *db, *dc;
	size_t s;
	int thd, blk;

	for (int i = 0; i < n; i++) {
		a[i] = rand() % UINT32_MAX/2;
		b[i] = rand() % UINT32_MAX/2;
	}

	s = n*sizeof(uint32_t);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);

	thd = 256;
	blk = (n+thd-1)/thd;

	k_randsum<<<thd, blk>>>(n, da, db, dc);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}
