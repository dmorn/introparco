#include <time.h>

typedef long duration;

int now(struct timespec *t);
duration sub(struct timespec *tic);
double ms(duration d);
