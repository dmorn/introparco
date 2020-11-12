#include <stdint.h>

#ifdef __cplusplus
#define LINKAGE "C"
#else
#define LINKAGE
#endif

extern LINKAGE void randsum(int n, uint32_t *a, uint32_t *b, uint32_t *c);
