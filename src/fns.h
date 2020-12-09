#ifdef __cplusplus
extern "C" {
#endif

void sumalloc(int n, uint **a, uint **b, uint **c);
void scanalloc(int n, uint a[], uint b[]);
void hostfree(void *ptr);

void sum(Msr *m, int n, uint a[], uint b[], uint c[]);
void scan(Msr *m, int n, uint a[], uint b[]);

double now(void);
void addmsr(Msr *lp, Msr *m);
void msrprintall(FILE *fout, Msr *lp);

#ifdef __cplusplus
}
#endif
