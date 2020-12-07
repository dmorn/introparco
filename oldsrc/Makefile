ROOT=.
include Make.conf

export CC = gcc
export CFLAGS = -ansi -Wall -pedantic -O

export LD = gcc
export LDFLAGS = -O

BUILD = build

$(BUILD)/%:
	$(MAKE) -C $(@F) $(@F)
	ln -sf ../$(@F)/$(@F) $@

clean:
	$(MAKE) -C rsv0 clean
	rm -rf $(BUILD)/*

