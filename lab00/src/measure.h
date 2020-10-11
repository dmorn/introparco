#include <time.h>

typedef long duration;

extern duration ns;
extern duration ms;

int now(struct timespec *t);
duration sub(struct timespec *tic);
