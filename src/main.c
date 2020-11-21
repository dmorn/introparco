#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "exp.h"

int debug = 1;

int
usage(int code, char *s) {
	fprintf(stderr, "usage: %s [n...n]\n", s);
	return code;
}

int
main(int argc, char *argv[]) {
	int i;

	for (i = 1; i < argc; i++) {
		char *err;
		int n;
		char *opt = argv[i];

		if ((n = atoi(opt)) < 0) {
			perror(strcat("invalid input ",opt));
			return usage(n, argv[0]);
		}

		fprintf(stderr, "%s (n: %d)\n", expdesc, n);
		if ((err = runexp(n)) != NULL) {
			fprintf(stderr, "%s\n", err);
			free(err);
			return 1;
		}
	}
	return 0;
}

