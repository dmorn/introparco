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
putsm(int fd, Measurement m, char *prefix) {
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
	Sumprefix
};

typedef void(*Exp)(int n, Measurement *m);

Exp exptbl[] = {
	[Randsum] = &randsumExp,
	[Sumprefix] = &sumprefixExp
};

int
usage(char *prog) {
	fprintf(stderr, "usage: %s <flags> (at least one algorithm has to be specified)\n", prog);
	fprintf(stderr, "-r execute random sum algorithm\n");
	fprintf(stderr, "-p execute sum prefix algorithm\n");
	fprintf(stderr, "-d turn on algorithmic specific debug prints\n");
	fprintf(stderr, "-n: specify size of the array handled (defaults to 100)\n");
	return 1;
}

int
main(int argc, char *argv[]) {
	unsigned int opt = 0;
	int n = 100, c, todo = 0;
	Measurement *m;
	debugfd = open("/dev/null", O_WRONLY);

	while((c = getopt(argc, argv, "rpdn:")) != -1) {
		switch (c) {
			case 'r':
				opt |= Randsum;
				todo++;
				break;
			case 'p':
				opt |= Sumprefix;
				todo++;
				break;
			case 'd':
				debugfd = 2;
				break;
			case 'n':
				n = atoi(optarg);
				if(n < 0) {
					return usage(argv[0]);
				}
				break;
			default:
				return usage(argv[0]);
		}
	}
	if(!opt)
		return usage(argv[0]);

	m = malloc(sizeof(Measurement));
	m->n = n;
	if(opt & Randsum) {
		randsumExp(n, m);
		putsm(1, *m, "randsum");
	}
	if(opt & Sumprefix) {
		sumprefixExp(n, m);
		putsm(1, *m, "sumprefix");
	}
	free(m);
}
