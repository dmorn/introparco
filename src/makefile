export CC = gcc
export CFLAGS = -c -ansi -Wall -pedantic -g

export LD = gcc
export LDFLAGS = -g
export NVLDFLAGS = -L$(CUDA_HOME)/lib64 -lcudart -lstdc++

export NVCC = nvcc
export NVCFLAGS = -c

BUILD = build

all: $(BUILD)/r.s0 $(BUILD)/r.p0 $(BUILD)/r.p1 $(BUILD)/r.p2 $(BUILD)/r.p3 $(BUILD)/r.p4 $(BUILD)/r.p5

serial/%.o: serial/%.c
	$(MAKE) -C serial $(notdir $@)

cuda/%.o: cuda/%.cu
	$(MAKE) -C cuda $(notdir $@)

%.o: %.c
	$(CC) $(CFLAGS) $^

%.o: %.cu
	$(NVCC) $(NVCFLAGS) -o $@ $^

# serial implementation using CPU only of randsum
$(BUILD)/r.s0: main.o serial/exp.o serial/r.o
	$(LD) $^ -o $@ $(LDFLAGS)

# handles randsum in a kernel
$(BUILD)/r.p0: cuda/r0.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

# uses mapped memory
$(BUILD)/r.p1: cuda/r1.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

# does not cleanup device memory
$(BUILD)/r.p2: cuda/r2.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

# uses __restrict__ and const, based on p1
$(BUILD)/r.p3: cuda/r3.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

# avoid unregistering paged memory
$(BUILD)/r.p4: cuda/r4.o serial/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)

# uses cudaHostAlloc and the cuda version of exp.cu
$(BUILD)/r.p5: cuda/r5.o cuda/exp.o main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(NVLDFLAGS)
clean:
	rm -f *.o *.gch build/*
	$(MAKE) -C serial clean
	$(MAKE) -C cuda clean

