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
printmsr(Msr *lp, void *arg) {
	FILE *fout;
	char *u;

	if(lp == NULL) {
		return;
	}
	fout = (FILE*)arg;

	switch(lp->unit) {
	case UnitBS:
		u = "bytes/sec";
		break;
	case UnitNS:
		u = "ns";
		break;
	case UnitMS:
		u = "ms";
		break;
	default:
		return;
	}
	fprintf(fout, "m,%s,%s,%.3f\n", u, lp->name, lp->val);
}

Msr*
newmsr(enum Unit u, char *n, float v) {
	Msr *p = malloc(sizeof(Msr));
	p->unit = u;
	p->name = n;
	p->val = v;
	p->next = NULL;
	return p;
}

Msr*
msrzero(void) {
	return newmsr(UnitNA, "", 0);
}

void
printallmsr(FILE *fout, Msr *lp) {
	msrapply(lp, printmsr, fout);
}

void
addmsr(Msr *lp, Msr *m) {
	for(; lp->next != NULL; lp = lp->next)
		;

	/* An optimization: if the first item is
	 * not initialized, replace it */
	if(lp->unit == UnitNA) {
		*lp = *m;
	} else {
		lp->next = m;
	}
}

void
freemsr(Msr *lp) {
	Msr *next;
	for(; lp != NULL; lp = next) {
		next = lp->next;
		free(lp);
	}
}
