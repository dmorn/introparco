#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "randsum.h"
#include "exp.h"

char*
runexp(int n) {
	int i;
	uint *a, *b, *c;
	char *err;

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
		if(debug)
			fprintf(stderr, "%d,%d,%d\n", a[i], b[i], c[i]);
		if(c[i] != a[i] + b[i]) {
			err = malloc(sizeof(char)*90);
			sprintf(err, "invalid output @ %d (a: %d, b: %d, c: %d)", i, a[i], b[i], c[i]);
			return err;
		}
	}

	free(a);
	free(b);
	free(c);
	return NULL;
}
