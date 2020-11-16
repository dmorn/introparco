CC = gcc
CFLAGS = -c -ansi -Wall -pedantic -g

LD = gcc
LDFLAGS = -g
NVLDFLAGS = -L$(CUDA_HOME)/lib64 -lcudart -lstdc++

NVCC = nvcc
NVCFLAGS = -c

all: randsum randsum.cuda

%.o: %.c
	$(CC) $(CFLAGS) $^
cuda/%.o: cuda/%.cu
	nvcc $(NVCFLAGS) -o $@ $^

randsum.cuda: cuda/randsum.o randsumexp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

randsum: port.o main.o randsumexp.o
	$(LD) $^ -o $@ $(LDFLAGS)

clean:
	rm *.o *.gch cuda/*.o

