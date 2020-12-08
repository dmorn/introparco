ROOT=.
CONF?=macos
include Make.conf

TARGS+=sum sumcheck

all: $(TARGS)

sum: cmd/sum/main.o libsum.a
	$(LD) $^ -o $@ $(LDFLAGS)

sumcheck: cmd/sumcheck/main.o
	$(LD) $^ -o $@ $(LDFLAGS)

libsum.a: sum.o mem.o msr.o
	$(AR) rs $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o *.a
	rm -f cmd/sum/*.o
	rm -f $(TARGS)
