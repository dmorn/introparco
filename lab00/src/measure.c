#include <time.h>
#include "measure.h"

duration ns = 1000000000;
duration ms = ns/1000;

int
now(struct timespec *t) {
	return clock_gettime(CLOCK_MONOTONIC_RAW, t);
}

duration
sub(struct timespec *tic) {
	int err;
	duration tocns, ticns;
	struct timespec toc;

	if ((err = now(&toc)))
		return err;
	tocns = (duration)(toc.tv_sec*ns + toc.tv_nsec);
	ticns = (duration)(tic->tv_sec*ns + tic->tv_nsec);
	return tocns - ticns;
}
