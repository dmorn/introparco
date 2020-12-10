#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "dat.h"
#include "fns.h"

void
allocsum(int n, uint **a, uint **b, uint **c) {
	*a = malloc(sizeof(uint)*n);
	*b = malloc(sizeof(uint)*n);
	*c = malloc(sizeof(uint)*n);
}

void
hfree(void *ptr) {
	free(ptr);
}
