RELNAME ?= release
RELARCHIVE ?= $(RELNAME).tgz
SRC = src

all:
	$(MAKE) -C $(SRC)

archive: $(RELARCHIVE)
$(RELARCHIVE): *
	$(MAKE) -C $(SRC) -i clean
	tar -zc $^ > $@

clean:
	$(MAKE) -C $(SRC) -i clean
	rm *.tgz
