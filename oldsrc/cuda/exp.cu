#include <cuda.h>
#include <limits.h>
#include <stdio.h>
#include "../r.h"
#include "../exp.h"

int
runexp(int n) {
	int i;
	size_t s;
	uint *a, *b, *c;

	s = n*sizeof(uint);
	/* note we're not checking for possible mem errors */
	cudaHostAlloc((void **)&a, s, cudaHostAllocWriteCombined);
	cudaHostAlloc((void **)&b, s, cudaHostAllocWriteCombined);
	cudaHostAlloc((void **)&c, s, cudaHostAllocPortable);
	for(i = 0; i < n; i++) {
		a[i] = rand() % UINT_MAX/2;
		b[i] = rand() % UINT_MAX/2;
		c[i] = 0;
	}
	randsum(n, a, b, c);

	/* output validation */
	for(i = 0; i < n; i++) {
		if(c[i] != a[i] + b[i]) {
			fprintf(stderr, "invalid output @ %d (a: %d, b: %d, c: %d)", i, a[i], b[i], c[i]);
			return n;
		}
	}

	cudaFreeHost(a);
	cudaFreeHost(b);
	cudaFreeHost(c);
	return 0;
}
