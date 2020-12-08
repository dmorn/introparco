#include <stdio.h>
#include "../../dat.h"

int
usage(int code, char *progname) {
	fprintf(stderr, "usage: %s\n", progname);
	fprintf(stderr, "checks the validity of sum's output, read from stdin\n");
	return code;
}

int
main(int argc, char *argv[]) {
	uint n, i, err;
	uint a, b, c;

	if((err = scanf("%u\n", &n)) < 1) {
		fprintf(stderr, "failed scanning number of items\n");
		return usage(err, argv[0]);
	}
	if(n < 0)
		return usage(2, argv[0]);

	for(i = 0; i < n; i++) {
		/* adding 2 to the index to reflect the line number required to
		 * find the error in the file */
		if((err = scanf("%u,%u,%u\n", &a, &b, &c)) < 3) {
			fprintf(stderr, "read line %d: %d\n", i+2, err);
			return usage(err, argv[0]);
		}
		if(c != a + b) {
			fprintf(stderr, "line %u validation failed: %u != %u + %u\n", i+2, c, a, b);
			return 2;
		}
	}

	printf("👍\n");
	return 0;
}
