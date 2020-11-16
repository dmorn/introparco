RELNAME ?= release
RELARCHIVE ?= $(RELNAME).tgz

release: $(RELARCHIVE)
$(RELARCHIVE): *
	tar -zc $^ > $@

