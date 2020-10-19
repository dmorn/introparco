USER = dmorandini
HOST = slurm-ctrl.inf.unibz.it
ADDR = $(USER)@$(HOST)

SRC = src

REV ?= $(shell git rev-parse --short HEAD)
export RELNAME = release-$(REV)
export RELARCHIVE = $(RELNAME).tar.gz
export CMD = benchmark
EXEC = $(CMD)-$(REV)

HOSTDIST = dist-$(shell basename $(PWD))
HOSTREL = $(HOSTDIST)/$(RELNAME)

.PHONY : deploy

deploy :
	cd $(SRC) && $(MAKE) release
	ssh $(ADDR) "rm -r $(HOSTREL); mkdir -p $(HOSTREL)"
	scp $(SRC)/$(RELARCHIVE) $(ADDR):.
	ssh $(ADDR) "tar -zxf $(RELARCHIVE) -C $(HOSTREL); rm $(RELARCHIVE)"
	ssh $(ADDR) "cd $(HOSTREL); make && mv $(CMD) ../../$(EXEC)"
	@echo $(EXEC) deployed!
