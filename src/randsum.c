#include <limits.h>
#include <stdlib.h>
#include <stdint.h>

void
randsum(int n, uint32_t *a, uint32_t *b, uint32_t *c) {
	for (int i = 0; i < n; i++) {
		a[i] = rand() % UINT32_MAX/2;
		b[i] = rand() % UINT32_MAX/2;
		c[i] = a[i] + b[i];
	}
}
