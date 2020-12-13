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

sum-cuda: cmd/sum/main.o cuda/libsum.a msr.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

sum-cudastream: cmd/sum/main.o cuda/libsumstream.a msr.o
	$(LD) $^ -o $@ $(LDFLAGS) $(LDADD)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

libsum.a: sum.o mem.o
	$(AR) rs $@ $^

cuda/libsum.a:
	(cd $(@D); $(MAKE))

cuda/libsumstream.a: sum.o mem.o
	(cd $(@D); $(MAKE))

clean:
	rm -f *.o *.a
	rm -f cmd/sum/*.o cmd/sumcheck/*.o
	rm -f $(TARGS)
	(cd cuda; make clean)
