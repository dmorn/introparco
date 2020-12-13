#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "event.h"
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
	Event *e;

	e = newevent();
	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);

	start(e, 0);
	cudaMemcpy(da, a, s, cudaMemcpyHostToDevice);
	cudaMemcpy(db, b, s, cudaMemcpyHostToDevice);
	addmsr(lp, newmsr(UnitMS, "cudaMemcpyHtD", stop(e, 0)));

	thd = 32;
	blk = (n+thd-1)/thd;

	start(e, 0);
	k_sum<<<blk, thd>>>(n, da, db, dc);
	addmsr(lp, newmsr(UnitMS, "k_sum", stop(e, 0)));

	start(e, 0);
	cudaMemcpy(c, dc, s, cudaMemcpyDeviceToHost);
	addmsr(lp, newmsr(UnitMS, "cudaMemcpyDtH", stop(e, 0)));

	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	freeevent(e);
}
