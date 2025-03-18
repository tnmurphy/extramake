## Extramake ##

**Author: Timothy N Murphy <tnmurphy@gmail.com>**

GNU make offers many functions like `$(subst ...) $(patsubst ...) $(filter ...)`
... but until v4 there was no way to add more.

Now there load directive which lets you add newly defined functions
written in C. In your makefile you add: 


```
    -load my_module.o
```

my_module.o can be compiled from my_module.c by instructions supplied
in the body of your makefile.

Extramake is a set of loadable modules for GNU make starting with 4.1 
that add functions for a wide variety of purposes.

## Functions offered in extramake ##

* $(equals x,y) tests string equality. Returns empty if the 2 parameters don't match or the value if they do. 
  * e.g. `FILENAME=file.$(if $(equals $(compression_level),0),tar,.tar.bz3)`
* $(siphash24 text[,key]) returns a 16 character hash of the input text, an optional key can be used to make the whole thing cryptographic.
* $(strlen <string>) returns the number of characters in <string>
* $(sum <number> <number> .... <number> )  finds the sum of a list of integers. Negative integers are allowed.  Any non-numeric characters will cause the empty string to be returned.
* $(mul <n> <n> <n>) returns the result of multiplying a list of numbers.  Overflow can occur. The platform's "long long" is used.
* $(lt x,y) returns 1 if x < y for integers x and y, empty string otherwise.
* $(lte x,y) returns 1 if x <= y for integers x and y, empty string otherwise.
* $(gt x,y) returns 1 if x >= y for integers x and y, empty string otherwise.
* $(gte x,y) returns 1 if x >= y for integers x and y, empty string otherwise.


## How to use the modules ##
Currently these modules build on Linux but they are intended to be portable
so it shouldn't be too hard to get them working on Windows.

The modules aren't hard to build but I have included some examples of how
it could be done.

Here is a very simple example where the module is assumed to be built and 
exist already This is just for the sake of explanation:

```
-load ./hash.o

SOURCES:=proga.c progb.c
OBJECTS:=$(SOURCES:.c=.o)
SOURCES_SUM:=$(siphash24 $(SOURCES))

# The name of the output depends on what the input file list is:
output_$(SOURCES_SUM): $(SOURCES)
    gcc -o $@ $^
```

The following example shows how one might build a shared library in a
way that makes use of the $(siphash24 ) function.  the xtra.mk file
is included into the main program makefile and then the hash module
is loaded.


```
# Generate a library with a version number that is based on
# the list of source files - so if you add or remove a 
# source file then the library will be rebuilt.  This is something 
# which often doesn't work properly in makefiles. It makes
# use of the siphash24 module to generate a short unique string
# based on the list of files

SOURCES:=proga.c progb.c
OBJECTS:=$(SOURCES:.c=.o)


## definitions that help with building 
## whatever module you decide to load.
include ../xtra.mk
XTRA_OUTPUTDIR:=.
XTRA_SOURCE:=..
## extramake stuff ends

# load the module if it's there or create a target to
# build it if not:
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

# Here the code to build the module is included. 
include ../hash.mk

clean:
	rm $(OBJECTS) $(LIBNAME) $(LIBSHORTNAME)
```


## How to add Functions ##


For example you can create an equality test that works in an expression (ifeq can't be used as part of an expression obviously). For example

```
  FILENAME=file.$(if $(equals $(compression_level),0),tar,.tar.bz3)
```

The C for this function (without includes and export directives):

```
  char *
  func_equals (const char *func_name, unsigned int argc, char **argv)
  {
      char *result = NULL;

      if (strcmp(argv[0], argv[1]) == 0) {
          result = gmk_alloc(strlen(argv[0]) + 1); /* not handling failure for simplicity */
          strcpy(result, argv[0]);
      }
    
      return result;
  }
```

This can be done with a macro but it's ugly and verbose. Macros also slow makefile parsing a lot and for a large build like e.g. an operating system this makes a big difference - it's a penalty you pay every time you run "make" even if you only changed 1 file.

There are plenty of things you cannot do with macros too. $(shell) is a get out card but it drastically slows down large makefiles.

Your module has a setup function which gets called when it's loaded and this adds the function into gmake:

```
  int
  equals_gmk_setup (const gmk_floc *flocp)
  {
      gmk_add_function ("equals", func_equals, 2, 2, GMK_FUNC_DEFAULT);
      return 1;
  }
```

