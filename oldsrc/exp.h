/* runs the experiment with array size n. Returns 0 if all goes well,
 * prints an error to stderr otherwise. */

#ifdef __cplusplus
#define LINKAGE "C"
#else
#define LINKAGE
#endif

extern LINKAGE int runexp(int n);

