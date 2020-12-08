NVCC=nvcc
NVCCFLAGS=-c

LIBS=libsum.a
all: $(LIBS)

libsum.a: sum.o mem.o
	$(AR) rs $@ $^

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $^
clean:
	rm -f *.o *.a
