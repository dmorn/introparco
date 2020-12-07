#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../fns.h"

int
usage(int code, char *progname) {
	fprintf(stderr, "usage: %s [task size]\n", progname);
	return code;
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

