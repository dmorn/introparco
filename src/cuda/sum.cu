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
	uint *da, *db, *dc;
	size_t s;
	int thd, blk;
	double tic;
	Msr *m1, *m2, *m3, *m4;
	Msr m = {MuNS, "sum", 0, NULL};
	Msr m1 = {MuNS, "cudaMemcpyHtD", 0, NULL};
	Msr m2 = {MuNS, "cudaMalloc", 0, NULL};
	Msr m3 = {MuNS, "cudaMallocDtH", 0, NULL};

	tic = now();
	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);
	m1 = msrnew(MuNS, "cudaMalloc", (uint)(now()-tic));
	msradd(lp, m1);

	tic = now();
	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);
	m2 = msrnew(MuNS, "cudaMemcpyHtoD", (uint)(now()-tic));
	msradd(lp, m2);

	thd = 32;
	blk = (n+thd-1)/thd;

	tic = now();
	k_sum<<<blk, thd>>>(n, da, db, dc);
	m3 = msrnew(MuNS, "sum", (uint)(now()-tic));
	msradd(lp, m3);

	tic = now();
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);
	m4 = msrnew(MuNS, "cudaMemcpyDtoH", (uint)(now()-tic));
	msradd(lp, m4);

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
}

