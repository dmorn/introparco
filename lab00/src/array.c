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
	int err;
	struct timespec t;
	duration elapsed;
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

	if ((err = now(&t))) {
		perror("now");
		return err;
	}
	for (int i = 0; i < n; i++) {
		a[i] = rand() % INT_MAX/2;
		b[i] = rand() % INT_MAX/2;
		c[i] = a[i] + b[i];
	}
	if ((elapsed = sub(&t)) < 0) {
		perror("sub");
		return elapsed;
	}
	for (int i = 0; i < n; i++) {
		fprintf(stdout, "%d\n", c[i]);
	}

	fprintf(stderr, "n=%d\n", n);
	fprintf(stderr, "elapsed=%.3fms\n", ms(elapsed));

	free(a);
	free(b);
	free(c);

	return 0;
}
