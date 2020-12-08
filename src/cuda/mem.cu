#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <cuda.h>
#include "../dat.h"
#include "../fns.h"

void
sumalloc(int n, uint **a, uint **b, uint **c) {
	size_t s = sizeof(uint)*n;
	/* notice we're not checking for errors */
	cudaHostAlloc(a, s, cudaHostAllocWriteCombined);
	cudaHostAlloc(b, s, cudaHostAllocWriteCombined);
	cudaHostAlloc(c, s, cudaHostAllocDefault);
}

void
hostfree(void *ptr) {
	cudaFreeHost(ptr);
}

