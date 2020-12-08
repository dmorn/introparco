SRC=src
REV?=$(shell git rev-parse --short HEAD)
TARG=archive-$(REV).tgz
TMPSRC=src.$(REV)

# Create a clean archive leaving the source
# directory unchanged.
$(TARG): $(TMPSRC)
	make -C $(TMPSRC) clean
	tar cz $(TMPSRC) >$@

$(TMPSRC): $(SRC)
	cp -r $(SRC) $(TMPSRC)

clean:
	rm -f $(TARG)
	rm -rf $(TMPSRC)

