#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "dat.h"
#include "fns.h"

void* 
hostalloc(size_t s) {
	return malloc(s);
}

void
hostfree(void *ptr) {
	free(ptr);
}
