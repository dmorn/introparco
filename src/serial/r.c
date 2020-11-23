/* contains portable versions of the algorithms implemented */

#include "../dat.h"
#include "../r.h"

void
randsum(int n, uint *a, uint *b, uint *c) {
	int i;
	for (i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
}
