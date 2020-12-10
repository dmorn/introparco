#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>
#include "../dat.h"
#include "../fns.h"

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	uint *da, *db, *dc;
	size_t s;

	s = n*sizeof(uint);
	cudaMalloc(&da, s);
	cudaMalloc(&db, s);
	cudaMalloc(&dc, s);
}
