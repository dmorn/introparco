SRC = src
BIN = bin
SCRIPTS = scripts

all:
	$(MAKE) -C $(SRC) all

%.tgz: makefile $(SCRIPTS) $(SRC) $(BIN)
	tar -zc $^ > $@

$(BIN)/%:
	$(MAKE) -C $(SRC) all

clean:
	$(MAKE) -C $(SRC) clean
	rm -f *.tgz
