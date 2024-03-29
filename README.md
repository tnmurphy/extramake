## Extramake ##

**Author: Timothy N Murphy <tnmurphy@gmail.com>**

Extramake is a set of loadable modules for GNU make starting with 4.1 
that add functions for a wide variety of purposes.

Funtions for simple maths, hashes, equality expressions,
etc are implemented to deal with specific pain points that
the author has experienced in several large build systems.

Currently these modules build on Linux but they are intended to be portable
so it shouldn't be too hard to get them working on Windows.
 
Example makefiles are included to show how to use each extension.

e.g.

```
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



```

## Functions ##

* $(equals x,y) tests string equality. Returns empty if the 2 parameters don't match or the value if they do
* $(siphash24 text[,key]) returns a 16 character hash of the input text, an optional key can be used to make the whole thing cryptographic.
* $(strlen <string>) returns the number of characters in <string>
* $(sum <number> <number> .... <number> )  finds the sum of a list of integers. Negative integers are allowed.  Any non-numeric characters will cause the empty string to be returned.
* $(mul <n> <n> <n>) returns the result of multiplying a list of numbers.  Overflow can occur. The platform's "long long" is used.
* $(lt x,y) returns 1 if x < y for integers x and y, empty string otherwise.
* $(lte x,y) returns 1 if x <= y for integers x and y, empty string otherwise.
* $(gt x,y) returns 1 if x >= y for integers x and y, empty string otherwise.
* $(gte x,y) returns 1 if x >= y for integers x and y, empty string otherwise.

