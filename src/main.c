#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>
#include "randsum.h"
#include "sumprefix.h"

int debugfd;

/* time interval since epoch in nanoseconds.
 * Exits if an error is encountered, hence it
 * just suitable for benchmarking. */
double
now(void) {
	struct timespec t;
	if (!timespec_get(&t, TIME_UTC))
		exit(5);
	return t.tv_sec*1e9 + t.tv_nsec;
}

typedef struct {
	char *ctx;
	char *algo;
	int n;
	double alloc;
	double free;
	double exec;

} Measurement;

void
putm(int fd, Measurement m) {
	dprintf(fd, "%s,%s,%d,%.0f,%.0f,%.0f\n", m.ctx, m.algo, m.n, m.alloc, m.free, m.exec);
}

extern void randsum(int n, uint32_t *a, uint32_t *b, uint32_t *c);

int
randsumExp(int n, Measurement *m) {
	long tic;
	uint32_t *a, *b, *c;

	tic = now();
	a = malloc(sizeof(uint32_t)*n);
	b = malloc(sizeof(uint32_t)*n);
	c = malloc(sizeof(uint32_t)*n);
	m->alloc = now() - tic;

	tic = now();
	randsum(n, a, b, c);
	m->exec = now() - tic;

	for (int i = 0; i < n; i++) {
		if (c[i] != a[i] + b[i])
			return 1;

		dprintf(debugfd, "%d,%d,%d\n", a[i], b[i], c[i]);
	}
	tic = now();
	free(a);
	free(b);
	free(c);
	m->free = now() - tic;
	return 0;
}

int
sumprefixExp(int n, Measurement *m) {
	long tic;
	uint32_t *a, *c;

	tic = now();
	a = malloc(sizeof(uint32_t)*n);
	c = malloc(sizeof(uint32_t)*n);
	m->alloc = now() - tic;

	tic = now();
	sumprefix(n, a, c);
	m->exec = now() - tic;

	for (int i = 0; i < n; i++) {
		if ((i) && c[i] != c[i-1] + a[i-1])
			return 1;

		dprintf(debugfd, "%d,%d\n", a[i], c[i]);
	}
	tic = now();
	free(a);
	free(c);
	m->free = now() - tic;
	return 0;
}

enum {
	Randsum = 1,
	Sumprefix,
};

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
			"-1 execute random sum algorithm\n"
			"-2 execute sum prefix algorithm\n"
			"-c: change ctx identifier (defaults to local)\n"
			"-d turn on algorithmic specific debug prints\n");
	return 1;
}

int
main(int argc, char *argv[]) {
	int opt = 0;
	int *todov;
	int c = 0, todoc = 0, todo = 0;
	Measurement *m;
	char *ctx = "local";
	debugfd = open("/dev/null", O_WRONLY);

	while((c = getopt(argc, argv, "12dc:")) != -1) {
		switch (c) {
			case 'c':
				ctx = optarg;
				break;
			case 'd':
				debugfd = 2;
				break;
			case '1':
				opt |= Randsum;
				break;
			case '2':
				opt |= Sumprefix;
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
	m->ctx = ctx;
	for(int i = 0; i < todoc; i++) {
		todo = todov[i];
		m->n = todo;
		if(opt & Randsum) {
			m->algo = algoids[Randsum];
			if(randsumExp(todo, m)) {
				fprintf(stderr, "error: invalid randsum output\n");
				return 2;
			}
			putm(1, *m);
		}
		if(opt & Sumprefix) {
			m->algo = algoids[Sumprefix];
			if(sumprefixExp(todo, m)){
				fprintf(stderr, "error: invalid sumprefix output\n");
				return 2;
			}
			putm(1, *m);
		}
	}

	free(todov);
	free(m);
}
