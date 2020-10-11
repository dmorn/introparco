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
main(int argc, char* argv[argc+1]) {
	int err;
	struct timespec t;
	duration elapsed;
	int acc;
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
	acc = 0;

	if ((err = now(&t))) {
		perror("now");
		return err;
	}
	for (int i = 0; i < n; i++) {
		a[i] = rand() % (INT_MAX/n);
		acc += a[i];
		c[i] = acc;
	}
	if ((elapsed = sub(&t)) < 0) {
		perror("sub");
		return elapsed;
	}
	for (int i = 0; i < n; i++) {
		fprintf(stdout, "%d,%d\n", a[i], c[i]);
	}

	fprintf(stderr, "n=%d\n", n);
	fprintf(stderr, "elapsed=%.3fms\n", (double)elapsed/ms);

	free(a);
	free(b);
	free(c);

	return 0;

}
