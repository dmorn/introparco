#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include "randsum.h"

void
randsum(int n, int *a, int *b, int *c) {
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		a[i] = rand() % INT_MAX/2;
		b[i] = rand() % INT_MAX/2;
		c[i] = a[i] + b[i];
	}
}
