#include <limits.h>
#include <stdlib.h>
#include "sumprefix.h"

void
sumprefix(int n, unsigned int *a, unsigned int *c) {
	int acc = 0;
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		a[i] = rand() % (UINT_MAX/n);
		acc += a[i];
		c[i] = acc;
	}
}
