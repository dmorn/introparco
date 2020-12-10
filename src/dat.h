#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint;

enum Unit {
	UnitNA,  /* Not Available */
	UnitMS,  /* Milliseconds */
	UnitNS,  /* Nanoseconds */
	UnitBS,  /* Bytes per Second */
};

typedef struct Msr Msr;

/* A measurement */
struct Msr {
	enum Unit unit;
	char       *name;
	float      val;
	Msr        *next; /* in list */
};

#ifdef __cplusplus
}
#endif
