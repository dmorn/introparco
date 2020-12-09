#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dat.h"
#include "fns.h"

double
now(void) {
	struct timespec t;
	if (!timespec_get(&t, TIME_UTC))
		exit(5);
	return t.tv_sec*1e9 + t.tv_nsec;
}

void
msrapply(Msr *lp, void(*fn)(Msr*, void*), void *arg) {
	for(; lp != NULL; lp = lp->next)
		(*fn)(lp, arg);
}

void
msrprint(Msr *lp, void *arg) {
	FILE *fout;
	char *u;

	if(lp == NULL) {
		return;
	}
	fout = (FILE*)arg;

	switch(lp->unit) {
	case MuBPS:
		u = "bytes/sec";
		break;
	case MuNS:
		u = "ns";
		break;
	default:
		return;
	}
	fprintf(fout, "m,%s,%s,%u\n", u, lp->name, lp->val);
}

void
msrprintall(FILE *fout, Msr *lp) {
	msrapply(lp, &msrprint, fout);
}

void
addmsr(Msr *lp, Msr *m) {
	if(lp->unit == MuNA) {
		*lp = *m;
	} else {
		lp->next = m;
	}
}

