#include <cuda.h>

__global__ void
k_randsum(int n, uint *a, uint *b, uint *c) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	if(i < n) {
		c[i] = a[i] + b[i];
	}
}

__host__ void
hostmalloc(void **ptr, size_t size, uint flags) {
	cudaHostAlloc(ptr, size, flags);
}

__host__ void
hostfree(void **ptr) {
	cudaHostFree(ptr);
}


