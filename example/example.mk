# Generate a program with a version number that is based on
# the list of source files - so if you add or remove a 
# source file then the library will be rebuilt.  This makes
# use of the siphash24 module to generate a short unique string
# based on the list of files

SOURCES:=proga.c progb.c
OBJECTS:=$(SOURCES:.c=.o)


include ../xtra.mk
XTRA_OUTPUTDIR:=.
XTRA_SOURCE:=..
-load $(XTRA_OUTPUTDIR)/hash$(XTRA_EXT)

LIBVERSION:=$(siphash24 $(SOURCES))
LIBNAME:=prog.$(LIBVERSION).so
LIBSHORTNAME:=prog.so

$(LIBNAME): $(OBJECTS)
	cc -o $@ $^ -shared
	ln -sf $@ $(LIBSHORTNAME)

$(OBJECTS) : %.o : %.c 
	cc -c -o $@ -fPIC $^

include ../hash.mk

clean:
	rm $(OBJECTS) $(LIBNAME) $(LIBSHORTNAME)

