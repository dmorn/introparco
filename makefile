SRC = src
BIN = bin
SCRIPTS = scripts
SIZE ?= 67108864 # 2^26

all: *.txt

%.tgz: makefile scripts src bin
	tar -zc $^ > $@

$(BIN)/%:
	$(MAKE) -C $(SRC) all

%.nvprof: $(BIN)/%
	$(SCRIPTS)/srun.sh nvprof -o $@ --cpu-profiling on $^ $(SIZE)

%.txt: %.nvprof
	nvprof -i $^ --cpu-profiling-mode top-down 2> $@

%.csv: %.nvprof
	nvprof -i $^ --cpu-profiling-mode top-down --csv 2> $@

clean-nvprof:
	rm *.txt *.nvprof *.csv

clean: clean-nvprof
	$(MAKE) -C $(SRC) -i clean
	rm *.tgz *.nvprof *.nvprof
