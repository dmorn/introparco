SRC = src
BIN = bin
SCRIPTS = scripts
SIZE ?= 67108864 # 2^26

all: r.report r.cuda.report

%.tgz: README.txt makefile scripts src bin
	$(MAKE) -C $(SRC) -i clean
	tar -zc $^ > $@

$(BIN)/%:
	$(MAKE) -C $(SRC) all

%.nvprof: $(BIN)/%
	$(SCRIPTS)/srun.sh nvprof -o $@ --cpu-profiling on $^ $(SIZE)

%.report: %.nvprof
	nvprof -i $^ --cpu-profiling-mode top-down 2> $@

clean-report:
	rm *.report *.nvprof

clean: clean-report
	$(MAKE) -C $(SRC) -i clean
	rm *.tgz *.report *.nvprof
