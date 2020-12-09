#include <time.h>
#include <stdio.h>
#include "dat.h"
#include "fns.h"

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	int i;
	double tic;
	Msr *m;

	tic = now();
	for(i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
	m = msrnew(MuNS, "sum", (uint)(now()-tic));
	msradd(lp, m);
}
