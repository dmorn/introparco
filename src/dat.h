#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint;

enum Munit {
	MuNA,  /* Not Available */
	MuBPS, /* Bytes per Second */
	MuNS   /* Nanoseconds */
};

typedef struct Msr Msr;

/* A measurement */
struct Msr {
	enum Munit unit;
	char       *name;
	uint       val;
	Msr        *next; /* in list */
};

#ifdef __cplusplus
}
#endif
