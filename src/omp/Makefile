all: libsum.a

libsum.a: sum.o mem.o
	$(AR) rs $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
clean:
	rm -f *.o *.a
