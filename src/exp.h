/* runs the experiment n times. If the returned error is != NULL, it is
 * caller's responsibility to release the resource when done. */
char* runexp(int n);

/* the experiment description, used for debug logs. exp implementations should
 * override its value */
extern char *expdesc;

/* set by exp callers, used to indicate wether debug information should be
 * printed to stderr */
extern int debug;
