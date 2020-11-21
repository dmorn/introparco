CC = gcc
CFLAGS = -c -ansi -Wall -pedantic -g

LD = gcc
LDFLAGS = -g
NVLDFLAGS = -L$(CUDA_HOME)/lib64 -lcudart -lstdc++

NVCC = nvcc
NVCFLAGS = -c
BUILD = build

all: $(BUILD)/r $(BUILD)/r.cuda

%.o: %.c
	$(CC) $(CFLAGS) $^

%.o: %.cu
	nvcc $(NVCFLAGS) -o $@ $^

$(BUILD)/r.cuda: kr.o rexp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

$(BUILD)/r: port.o main.o rexp.o
	$(LD) $^ -o $@ $(LDFLAGS)

clean:
	rm *.o *.gch build/*

