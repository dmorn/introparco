CFLAGS =

# Vectorization
# CFLAGS += -msse3 -mfpmath=sse -funroll-loops

# Vectorization Darwin
# CFLAGS += -ftree-vectorizer-verbose
# Vectorization Linux
# CFLAGS += -ftree-vectorizer-verbose=5

# Optimization
# CFLAGS += -O3

# OpenMP
# CFLAGS += -fopenmp
# OpenMP Darwin
# CFLAGS += -Xpreprocessor -fopenmp

LDFLAGS =
# OpenMP Darwin
# LDFLAGS += -Xpreprocessor -fopenmp -lomp
# OpenMP
# LDFLAGS += -fopenmp
LDFLAGS += -lcudart -L/usr/local/cuda-10.2/lib64

CC = gcc
VCC = nvcc
LD = gcc

CMD ?= benchmark
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
$(RELARCHIVE) : *.c *.cu *.h *.sh *.dat makefile
	tar -zc $^ > $@

randsum.o : randsum.c randsum.h
	$(VCC) -c $(CFLAGS) randsum.cu
sumprefix.o : sumprefix.c sumprefix.h
	$(CC) -c $(CFLAGS) sumprefix.c
benchmark.o : benchmark.c sumprefix.h randsum.h
	$(CC) -c $(CFLAGS) benchmark.c

$(CMD) : benchmark.o sumprefix.o randsum.o
	$(LD) $(LDFLAGS) $^ -o $@
