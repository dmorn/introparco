#include <time.h>

typedef int64_t duration;

int now(struct timespec *t);
duration sub(struct timespec *tic);
double ms(duration d);
