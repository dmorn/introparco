#include <time.h>

typedef long duration;

extern const duration ns;
extern const duration ms;

int now(struct timespec *t);
duration sub(struct timespec *tic);
