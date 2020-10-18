#include <limits.h>
#include <stdlib.h>
#include "sumprefix.h"

void
sumprefix(int n, int *a, int *c) {
	int acc = 0;
	for (int i = 0; i < n; i++) {
		a[i] = rand() % (INT_MAX/n);
		acc += a[i];
		c[i] = acc;
	}
}
