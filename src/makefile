CC=gcc

# c11 is required for get_timespec only.
CFLAGS=-std=c11 -Wall -pedantic -O

LD=gcc
LDFLAGS=
LDADD=

ROOT=.
CONF?=posix
include Make.conf

# Add default args. Others are included by CONF-driven Makefiles.
TARGS+=sum sumcheck

all: $(TARGS)

sum: cmd/sum/main.o libsum.a msr.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

sumcheck: cmd/sumcheck/main.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

libsum.a: sum.o mem.o
	$(AR) rs $@ $^

sum-cuda-v1: cmd/sum/main.o cuda/libsum.a msr.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

cuda/libsum.a:
	(cd $(@D); $(MAKE))

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.a
	rm -f cmd/sum/*.o cmd/sumcheck/*.o
	rm -f $(TARGS)
	(cd cuda; make clean)
