
SOURCES:=proga.c progb.c
OBJECTS:=$(SOURCES:.c=.o)


include ../xtra.mk
XTRA_OUTPUTDIR:=.
XTRA_SOURCE:=..
-load $(XTRA_OUTPUTDIR)/hash$(XTRA_EXT)

LIBVERSION:=$(siphash24 $(SOURCES))
LIBNAME:=prog_$(LIBVERSION).so

$(LIBNAME): $(OBJECTS)
	cc -o $@ $^ -shared

$(OBJECTS) : %.o : %.c 
	cc -c -o $@ -fPIC $^

include ../hash.mk



