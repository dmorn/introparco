#include <time.h>
#include <stdio.h>
#include "dat.h"
#include "fns.h"

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	int i;
	double tic;
	Msr m = {MuNS, "sum", 0, NULL};

	tic = now();
	for(i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
	m.val = (uint)(now()-tic);

	addmsr(lp, &m);
}
