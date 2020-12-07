#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <cuda.h>
#include "../fns.h"

int
usage(int code, char *progname) {
	fprintf(stderr, "usage: %s [task size]\n", progname);
	return code;
}

void
randsum(int n, uint *a, uint *b, uint *c) {
	int i;
	for (i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
}

int
run(int n) {
	int i;
	uint a[], b[], c[];
	size_t s;

	s = sizeof(uint)*n;

	/* WriteCombined improves host->device transfers */
	hostmalloc((void **)&a, s, cudaHostAllocWriteCombined);
	hostmalloc((void **)&b, s, cudaHostAllocWriteCombined);
	hostmalloc((void **)&c, s, cudaHostAllocDefault);
	for(i = 0; i < n; i++) {
		a[i] = rand();
		b[i] = rand();
	}
	randsum(n, a, b, c);

	/* output validation */
	for(i = 0; i < n; i++) {
		if(c[i] != a[i] + b[i]) {
			fprintf(stderr, "invalid output @ %d (a: %d, b: %d, c: %d)", i, a[i], b[i], c[i]);
			return n;
		}
	}

	hostfree(a);
	hostfree(b);
	hostfree(c);
	return 0;
}

int
main(int argc, char *argv[]) {
	int n;
	char *opt;
	if (argc < 2)
		return usage(2, argv[0]);

	opt = argv[1];
	if ((n = atoi(opt)) < 0) {
		perror(strcat("invalid input ",opt));
		return usage(n, argv[0]);
	}
	return run(n);
}

