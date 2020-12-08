#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "../../dat.h"
#include "../../fns.h"

int
usage(int code, char *progname) {
	fprintf(stderr, "usage: %s\n", progname);
	fprintf(stderr, "reads from stdin, expecing a line telling the\n"
			"number of records that fill follow, then 2 records\n"
			"each line separated by a comma. Each record is\n"
			"parsed as an unsigned interger.\n");
	return code;
}

int
main(int argc, char *argv[]) {
	uint n, fa, fb;
	uint *a = NULL;
	uint *b = NULL;
	uint *c = NULL;
	int err, i;
	Msr m = {MuNA, "", 0, NULL};

	if((err = scanf("%u\n", &n)) < 1) {
		fprintf(stderr, "failed scanning number of items\n");
		return usage(err, argv[0]);
	}
	if(n < 0)
		return usage(2, argv[0]);

	sumalloc(n, &a, &b, &c);

	for(i = 0; i < n; i++) {
		if((err = scanf("%u,%u\n", &fa, &fb)) < 2) {
			return usage(err, argv[0]);
		}
		a[i] = fa;
		b[i] = fb;
	}

	sum(&m, n, a, b, c);

	printf("%u\n", n);
	for(i = 0; i < n; i++)
		printf("%u,%u,%u\n", a[i], b[i], c[i]);

	printmsr(stderr, &m);

	fflush(stdout);
	fflush(stderr);

	hostfree(a);
	hostfree(b);
	hostfree(c);

	return 0;
}

