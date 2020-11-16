#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "../randsum.h"
#include "../exp.h"

char *expdesc = "randsum cuda with cuda kernel";

__global__
void
k_randsum(int n, uint *a, uint *b, uint *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

void
randsum(int n, uint *a, uint *b, uint *c) {
	uint *da, *db, *dc;
	size_t s;
	int thd, blk;

	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);

	thd = 256;
	blk = (n+thd-1)/thd;

	if(debug)
		fprintf(stderr, "thd: %d, blk: %d\n", thd, blk);
	k_randsum<<<thd, blk>>>(n, da, db, dc);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}

