export CC = gcc
export CFLAGS = -c -ansi -Wall -pedantic -g

export LD = gcc
export LDFLAGS = -g
export NVLDFLAGS = -L$(CUDA_HOME)/lib64 -lcudart -lstdc++

export NVCC = nvcc
export NVCFLAGS = -c

BUILD = build

all: $(BUILD)/r.s0 $(BUILD)/r.p0 $(BUILD)/r.p1

serial/%.o: serial/%.c
	$(MAKE) -C serial $(notdir $@)

cuda/%.o: cuda/%.cu
	$(MAKE) -C cuda $(notdir $@)

%.o: %.c
	$(CC) $(CFLAGS) $^

%.o: %.cu
	$(NVCC) $(NVCFLAGS) -o $@ $^

$(BUILD)/r.p0: cuda/r0.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)
$(BUILD)/r.p1: cuda/r1.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

$(BUILD)/r.s0: main.o serial/exp.o serial/r.o
	$(LD) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o *.gch build/*
	$(MAKE) -C serial clean
	$(MAKE) -C cuda clean

