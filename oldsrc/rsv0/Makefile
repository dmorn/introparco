ROOT=..
include $(ROOT)/Make.config
LIB=librsv0.a

OFILES=rs.o

all: $(LIB)
$(LIB): $(OFILES)
	$(AR) ars $(LIB) $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $<
clean:
	rm -f *.o $(TARG)

