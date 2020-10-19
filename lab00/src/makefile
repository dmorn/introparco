CFLAGS = -Wall -Wextra

# Vectorization
CFLAGS += -msse3 -mfpmath=sse -funroll-loops

# Vectorization Darwin
# CFLAGS += -ftree-vectorizer-verbose
# Vectorization Linux
CFLAGS += -ftree-vectorizer-verbose=5

# Optimization
# CFLAGS += -O3

# OpenMP

LDFLAGS =
CC = gcc

CMD ?= benchmark
BUILDDIR = build
BINDIR = /usr/local/bin

RELNAME ?= release
RELARCHIVE ?= $(RELNAME).tar.gz

.PHONY : deploy all install clean release

all : $(CMD)
install : $(CMD)
	mv $(CMD) $(BINDIR)
uninstall :
	rm $(BINDIR)/$(CMD)
clean :
	rm *.o
	rm *.tar.gz
	rm $(CMD)

release : $(RELARCHIVE)
$(RELARCHIVE) : *.c *.h makefile
	tar -zc $^ > $@

sumprefix.o : sumprefix.c sumprefix.h
	$(CC) -c $(CFLAGS) sumprefix.c
randsum.o : randsum.c randsum.h
	$(CC) -c $(CFLAGS) randsum.c
benchmark.o : benchmark.c sumprefix.h randsum.h
	$(CC) -c $(CFLAGS) benchmark.c
$(CMD) : benchmark.o sumprefix.o randsum.o
	$(CC) $(LDFLAGS) $^ -o $@
