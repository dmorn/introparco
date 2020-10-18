CMD = benchmark
BUILDDIR = build
BINDIR = /usr/local/bin
CFLAGS = -Wall -Wextra
LDFLAGS =
CC = cc

all : $(CMD)
install : $(CMD)
	mv $(CMD) $(BINDIR)
clean:
	rm *.o
	rm $(CMD)
	rm $(BINDIR)/$(CMD)

sumprefix.o : sumprefix.c sumprefix.h
	$(CC) -c $(CFLAGS) sumprefix.c
randsum.o : randsum.c randsum.h
	$(CC) -c $(CFLAGS) randsum.c
benchmark.o : benchmark.c sumprefix.h randsum.h
	$(CC) -c $(CFLAGS) benchmark.c
$(CMD) : benchmark.o sumprefix.o randsum.o
	$(CC) $(LDFLAGS) $^ -o $@
