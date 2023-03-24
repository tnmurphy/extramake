# Generate a program with a version number that is based on
# the list of source files - so if you add or remove a 
# source file then the library will be rebuilt.  This makes
# use of the siphash24 module to generate a short unique string
# based on the list of files

SOURCES:=proga.c progb.c
OBJECTS:=$(SOURCES:.c=.o)


# This section causes a hash generating/loading function (siphash24)
# from extramake to be built and loaded into GNU Make: 
include ../xtra.mk
XTRA_OUTPUTDIR:=.
XTRA_SOURCE:=..
-load $(XTRA_OUTPUTDIR)/hash$(XTRA_EXT)

# Now we're using the siphash function that was loaded above to
# create a unique version that is based on the list of source
# files. 
#
# Rationale: We want to rebuild the library not only when the source
# files change but when a new source file is added or one is removed.
# Even if that list of source files is very long the 
# hash of it will have a constant size (which is why we don't just
# concatenate all the filenames to make a version):
#
LIBVERSION:=$(siphash24 $(SOURCES))
LIBNAME:=prog.$(LIBVERSION).so
LIBSHORTNAME:=prog.so

# link the library and force a short symbolic link to point to it
# which other programs can use if they are not sensitive to some
# specific version:
$(LIBNAME): $(OBJECTS)
	cc -o $@ $^ -shared
	ln -sf $@ $(LIBSHORTNAME)

$(OBJECTS) : %.o : %.c 
	cc -c -o $@ -fPIC $^

include ../hash.mk

clean:
	rm $(OBJECTS) $(LIBNAME) $(LIBSHORTNAME)

