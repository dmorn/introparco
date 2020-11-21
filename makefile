RELNAME ?= release
RELARCHIVE ?= $(RELNAME).tgz

release: $(RELARCHIVE)
$(RELARCHIVE): *
	$(MAKE) -C src -i clean
	tar -zc $^ > $@

clean:
	rm *.tgz
