#include <time.h>
#include <stdio.h>
#include "dat.h"
#include "fns.h"

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	int i;
	double tic, toc;

	tic = now();
	for(i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
	toc = now();
	addmsr(lp, newmsr(UnitMS, "sum", elapsedms(tic, toc)));
}
