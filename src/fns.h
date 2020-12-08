#ifdef __cplusplus
extern "C" {
#endif

void sumalloc(int n, uint **a, uint **b, uint **c);
void scanalloc(int n, uint a[], uint b[]);
void hostfree(void *ptr);

void sum(Msr *m, int n, uint a[], uint b[], uint c[]);
void scan(Msr *m, int n, uint a[], uint b[]);

/* prints the measurement linked list. Each measurement will have
 * its own line. Exits printing an error if any occur. */
void printmsr(FILE *fout, Msr *m);

double now(void);
void addmsr(Msr *lp, Msr *m);

#ifdef __cplusplus
}
#endif
