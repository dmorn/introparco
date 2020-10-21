#include <limits.h>
#include <stdlib.h>
#include "randsum.h"

void
randsum(int n, unsigned int *a, unsigned int *b, unsigned int *c) {
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		a[i] = rand() % UINT_MAX/2;
		b[i] = rand() % UINT_MAX/2;
		c[i] = a[i] + b[i];
	}
}
