#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include "randsum.h"
#include "sumprefix.h"

int debugfd;

/* time interval since epoch in nanoseconds.
 * Exits if an error is encountered, hence it
 * just suitable for benchmarking. */
long
now(void) {
	struct timespec t;
	if (!timespec_get(&t, TIME_UTC))
		exit(5);
	return t.tv_sec*1e9 + t.tv_nsec;
}

typedef struct {
	int n;
	long alloc;
	long free;
	long exec;

} Measurement;

void
putm(int fd, Measurement m, char *prefix) {
	dprintf(fd, "%s,%d,%lu,%lu,%lu\n", prefix, m.n, m.alloc, m.free, m.exec);
}

void
randsumExp(int n, Measurement* m) {
	long tic;
	int *a, *b, *c;

	tic = now();
	a = malloc(sizeof(int)*n);
	b = malloc(sizeof(int)*n);
	c = malloc(sizeof(int)*n);
	m->alloc = now() - tic;

	tic = now();
	randsum(n, a, b, c);
	m->exec = now() - tic;

	for (int i = 0; i < n; i++) {
		dprintf(debugfd, "%d,%d,%d\n", a[i], b[i], c[i]);
	}
	tic = now();
	free(a);
	free(b);
	free(c);
	m->free = now() - tic;
}

void
sumprefixExp(int n, Measurement *m) {
	long tic;
	int *a, *c;

	tic = now();
	a = malloc(sizeof(int)*n);
	c = malloc(sizeof(int)*n);
	m->alloc = now() - tic;

	tic = now();
	sumprefix(n, a, c);
	m->exec = now() - tic;

	for (int i = 0; i < n; i++) {
		dprintf(debugfd, "%d,%d\n", a[i], c[i]);
	}
	tic = now();
	free(a);
	free(c);
	m->free = now() - tic;
}

enum {
	Randsum = 1,
	Sumprefix,
};

/* Exp function signature is shared across sumprefixExp and
 * randsumExp functions. */
typedef void(*Exp)(int n, Measurement *m);

char *algoids[] = {
	[Randsum] = "randsum",
	[Sumprefix] = "sumprefix"
};

int
usage(char *prog) {
	fprintf(stderr, "\n"
			"usage: %s <flags> <N>\n"
			"note: at least one algo has to be specified\n"
			"\n", prog);

	fprintf(stderr, "N: list of array sizes. Each n will be a separate measurement\n"
			"-r execute random sum algorithm\n"
			"-R: same as -r, but changes algo identifier\n"
			"-p execute sum prefix algorithm\n"
			"-P: same as -R with -p\n"
			"-d turn on algorithmic specific debug prints\n");
	return 1;
}

int
main(int argc, char *argv[]) {
	unsigned int opt = 0;
	int c = 0, todoc = 0, todo = 0;
	int *todov;
	Measurement *m;
	debugfd = open("/dev/null", O_WRONLY);

	while((c = getopt(argc, argv, "rpdn:R:P:")) != -1) {
		switch (c) {
			case 'r':
				opt |= Randsum;
				break;
			case 'R':
				opt |= Randsum;
				algoids[Randsum] = optarg;
				break;
			case 'p':
				opt |= Sumprefix;
				break;
			case 'P':
				opt |= Sumprefix;
				algoids[Sumprefix] = optarg;
				break;
			case 'd':
				debugfd = 2;
				break;
			default:
				return usage(argv[0]);
		}
	}
	if(!opt) {
		fprintf(stderr, "error: no algorithm was specified\n");
		return usage(argv[0]);
	}

	todoc = argc - optind;
	if(todoc <= 0) {
		fprintf(stderr, "error: at least one N has to be specified\n");
		return usage(argv[0]);
	}

	todov = malloc(sizeof(int)*todoc);
	for(int i = 0; i < todoc; i++) {
		todo = atoi(argv[i+optind]);
		if(todo < 0) {
			fprintf(stderr, "error: invalid N at position %d: %s\n", i, argv[i]);
			return usage(argv[0]);
		}
		todov[i] = todo;
	}

	m = malloc(sizeof(Measurement));
	for(int i = 0; i < todoc; i++) {
		todo = todov[i];
		m->n = todo;
		if(opt & Randsum) {
			randsumExp(todo, m);
			putm(1, *m, algoids[Randsum]);
		}
		if(opt & Sumprefix) {
			sumprefixExp(todo, m);
			putm(1, *m, algoids[Sumprefix]);
		}
	}

	free(todov);
	free(m);
}
