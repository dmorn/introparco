SRC = src
USER = dmorandini
HOST = slurm-ctrl.inf.unibz.it
ADDR = $(USER)@$(HOST)
REV = $(sh git rev-parse --short)
RELNAME = release-$(REV)
RELARCHIVE = $(RELNAME).tar.gz

release : $(RELARCHIVE)
$(RELARCHVE) : $(SRC)/*.c $(SRC)/makefile
	tar -xc $^ > $@

deploy : $(RELARCHIVE)
	ssh $(ADDR) mkdir $(RELDIR)
	scp $^ $(ADDR):$(RELDIR)/
