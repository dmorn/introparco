#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "../r.h"
#include "../exp.h"

__global__ void
k_randsum(int n, uint *a, uint *b, uint *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

void
randsum(int n, uint *a, uint *b, uint *c) {
	uint flags;
	uint *da, *db, *dc;
	size_t s;
	int thd, blk;

	flags = cudaHostRegisterMapped;
	s = n*sizeof(uint);
	cudaHostRegister(a, s, flags);
	cudaHostRegister(b, s, flags);
	cudaHostRegister(c, s, flags);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);

	thd = 256;
	blk = (n+thd-1)/thd;

	fprintf(stderr, "blk: %d, thd: %d\n", blk, thd);
	k_randsum<<<blk, thd>>>(n, da, db, dc);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);

	cudaHostUnregister(a);
	cudaHostUnregister(b);
	cudaHostUnregister(c);
	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}

