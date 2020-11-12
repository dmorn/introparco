CUDAHOME =
CFLAGS = -c -I$(CUDA_HOME)/include
LDFLAGS = -L$(CUDA_HOME)/lib64 -lcudart -lstdc++
CUDAFLAGS = -c

CC = gcc
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

randsum.o : randsum.cu randsum.h
	nvcc -o $@ randsum.cu $(CUDAFLAGS)

sumprefix.o : sumprefix.c sumprefix.h
	$(CC) $(CFLAGS) sumprefix.c

main.o : main.c sumprefix.h randsum.h
	$(CC) $(CFLAGS) main.c

$(CMD) : main.o sumprefix.o randsum.o
	$(LD) $^ -o $@ $(LDFLAGS)
