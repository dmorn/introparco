#include "dat.h"

#ifdef __cplusplus
#define LINKAGE "C"
#else
#define LINKAGE
#endif

/* Fills C with the sum of the contents of a and b */
extern LINKAGE void randsum(int n, uint *a, uint *b, uint *c);
extern LINKAGE int run(int n);
