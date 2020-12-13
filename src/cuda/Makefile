NVCC=nvcc
NVCCFLAGS=-c --default-stream per-thread

LIBS=libsum.a
all: $(LIBS)

libsum.a: sum.o mem.o event.o
	$(AR) rs $@ $^

libsumstream.a: sum.o mem.o event.o
	$(AR) rs $@ $^

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $^
clean:
	rm -f *.o *.a
