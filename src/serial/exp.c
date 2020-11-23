#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "../r.h"
#include "../exp.h"

int
runexp(int n) {
	int i;
	uint *a, *b, *c;

	a = malloc(sizeof(uint)*n);
	b = malloc(sizeof(uint)*n);
	c = malloc(sizeof(uint)*n);
	for(i = 0; i < n; i++) {
		a[i] = rand() % UINT_MAX/2;
		b[i] = rand() % UINT_MAX/2;
	}
	randsum(n, a, b, c);

	/* output validation */
	for(i = 0; i < n; i++) {
		if(c[i] != a[i] + b[i]) {
			fprintf(stderr, "invalid output @ %d (a: %d, b: %d, c: %d)", i, a[i], b[i], c[i]);
			return n;
		}
	}

	free(a);
	free(b);
	free(c);
	return 0;
}
