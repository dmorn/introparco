export CC=/usr/local/bin/gcc-10
export LD=/usr/local/bin/gcc-10

# c11 is required for get_timespec only.
export CFLAGS=-std=c11 -Wall -pedantic -O
export LDFLAGS=
export LDADD=

CONF?=omp
include Make.$(CONF)

# Add default args. Others are included by CONF-driven Makefiles.
TARGS+=sum sumcheck

all: $(TARGS)

sum: cmd/sum/main.o libsum.a msr.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

sumcheck: cmd/sumcheck/main.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

libsum.a: sum.o mem.o
	$(AR) rs $@ $^

clean:
	rm -f *.o *.a
	rm -f cmd/sum/*.o cmd/sumcheck/*.o
	rm -f $(TARGS)
	(cd cuda; make clean)
	(cd omp; make clean)
