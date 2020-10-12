#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "measure.h"

void
usage(char* name) {
	printf("%s <size of the array>\n", name);
}

int
main(int argc, char *argv[]) {
	long tic, toc;
	double elapsed;
	int *a, *b, *c;

	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}
	int n = atoi(argv[1]);
	if (n < 0) {
		usage(argv[0]);
		return 2;
	}

	a = malloc(sizeof(int)*n);
	b = malloc(sizeof(int)*n);
	c = malloc(sizeof(int)*n);

	tic = now_ns();
	for (int i = 0; i < n; i++) {
		a[i] = rand() % INT_MAX/2;
		b[i] = rand() % INT_MAX/2;
		c[i] = a[i] + b[i];
	}
	toc = now_ns();
	for (int i = 0; i < n; i++) {
		fprintf(stdout, "%d,%d,%d\n", a[i], b[i], c[i]);
	}

	fprintf(stderr, "n=%d\n", n);
	elapsed = (double)(toc - tic)/1e6;
	fprintf(stderr, "elapsed=%.3fms\n", elapsed);

	free(a);
	free(b);
	free(c);

	return 0;
}
