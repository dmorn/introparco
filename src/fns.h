#ifdef __cplusplus
extern "C" {
#endif

void allocsum(int n, uint **a, uint **b, uint **c);
void allocscan(int n, uint a[], uint b[]);
void hfree(void *ptr);

void sum(Msr *m, int n, uint a[], uint b[], uint c[]);
void scan(Msr *m, int n, uint a[], uint b[]);

double now(void);
Msr* newmsr(enum Unit u, char *n, float v);
Msr* msrzero(void);
void addmsr(Msr *lp, Msr *m);
void freemsr(Msr *lp);
void printallmsr(FILE *fout, Msr *lp);

#ifdef __cplusplus
}
#endif
