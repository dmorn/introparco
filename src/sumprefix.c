#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include "sumprefix.h"

void
sumprefix(int n, uint32_t *a, uint32_t *c) {
	int acc = 0;
	for (int i = 0; i < n; i++) {
		a[i] = rand() % (UINT_MAX/n);
		acc += a[i];
		c[i] = acc;
	}
}
