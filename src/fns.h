void* hostalloc(size_t s);
void hostfree(void *ptr);

void sum(Msr *m, int n, uint a[], uint b[], uint c[]);
void scan(Msr *m, int n, uint a[], uint b[]);

/* prints the measurement linked list. Each measurement will have
 * its own line. Exits printing an error if any occur. */
void printmsr(FILE *fout, Msr *m);

double now(void);
void addmsr(Msr *lp, Msr *m);
