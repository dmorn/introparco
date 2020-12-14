NVCC=nvcc
NVCCFLAGS=-c --default-stream per-thread

all: libsum.a libsumstream.a

libsum.a: sum.o mem.o event.o
	$(AR) rs $@ $^

libsumstream.a: sumstream.o mem.o event.o
	$(AR) rs $@ $^

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $^
clean:
	rm -f *.o *.a
