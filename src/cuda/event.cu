#include <cuda.h>
#include <stdlib.h>
#include "event.h"

void
start(Event *e, cudaStream_t s) {
	cudaEventRecord(e->tic, s);
}

float
stop(Event *e, cudaStream_t s) {
	float elaps;
	cudaEventRecord(e->toc, s);
	cudaEventSynchronize(e->toc);
	cudaEventElapsedTime(&elaps, e->tic, e->toc);

	return elaps;
}

void
freeevent(Event *e) {
	cudaEventDestroy(e->tic);
	cudaEventDestroy(e->toc);
	free(e);
}

Event*
newevent(void) {
	Event *e;
	e = (Event*) malloc(sizeof(Event));
	cudaEventCreate(&(e->tic));
	cudaEventCreate(&(e->toc));
	return e;
}
