#include <time.h>
#include "measure.h"

const duration d_ns = 1000000000;
const duration d_ms = d_ns / 1000;

int
now(struct timespec *t) {
	return clock_gettime(CLOCK_MONOTONIC_RAW, t);
}

double
ms(duration d) {
	return (double)d/d_ms;
}

duration
sub(struct timespec *tic) {
	int err;
	duration tocns, ticns;
	struct timespec toc;

	if ((err = now(&toc)))
		return err;
	tocns = (duration)(toc.tv_sec*d_ns + toc.tv_nsec);
	ticns = (duration)(tic->tv_sec*d_ns + tic->tv_nsec);
	return tocns - ticns;
}
