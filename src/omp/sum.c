#include <time.h>
#include <stdio.h>
#include "../dat.h"
#include "../fns.h"

void
sum(Msr *lp, int n, uint a[], uint b[], uint c[]) {
	int i;

#pragma omp parallel for shared(a,b,c,n) default(none)
	for(i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
}
