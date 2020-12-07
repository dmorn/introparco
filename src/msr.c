#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dat.h"
#include "fns.h"

void
printmsr(FILE *fout, Msr *m) {
	char *u;

	if(m == NULL) {
		fflush(fout);
		return;
	}

	switch(m->unit) {
	case MuBPS:
		u = "bytes/sec";
		break;
	case MuNS:
		u = "ns";
		break;
	default:
		fprintf(fout, "unrecognised measurement unit %d\n", m->unit);
		fflush(fout);
		exit(2);
	}
	fprintf(fout, "m,%s,%s,%u\n", u, m->name, m->val);
	printmsr(fout, m->next);
}

double
now(void) {
	struct timespec t;
	if (!timespec_get(&t, TIME_UTC))
		exit(5);
	return t.tv_sec*1e9 + t.tv_nsec;
}

void
addmsr(Msr *lp, Msr *m) {
	if(lp->unit == MuNA) {
		*lp = *m;
	} else {
		lp->next = m;
	}
}

