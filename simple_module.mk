include xtra.mk

define simplemodule

all:: $(XTRA_OUTPUTDIR)/$1$(XTRA_EXT)

-load $(XTRA_OUTPUTDIR)/$1$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/$1$(XTRA_EXT): $(XTRA_OUTPUTDIR)/$1.o
	gcc -shared -o $$@ $$^

$(XTRA_OUTPUTDIR)/$1.o: $(XTRA_SOURCE)/$1.c
	gcc $(XTRA_CFLAGS) -c $$^ -o $$@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$$(XTRA_CLEANTARGETS) \
    $(XTRA_OUTPUTDIR)/$1$(XTRA_EXT) $(XTRA_OUTPUTDIR)/$1.o 

test::

test::
	valgrind --track-origins=yes make -f test_$1.mk


endef

define moduleplus
$(call simplemodule,$1)

$(XTRA_OUTPUTDIR)/$1$(XTRA_EXT): $(XTRA_OUTPUTDIR)/$2.o

$(XTRA_OUTPUTDIR)/$2.o: $(XTRA_SOURCE)/$2.c
	gcc $(XTRA_CFLAGS) -c $$^ -o $$@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$$(XTRA_CLEANTARGETS) \
    $(XTRA_OUTPUTDIR)/$2.o 

test::
	valgrind --track-origins=yes make -f test_$1.mk

endef


ifeq ($(XTRA_CLEAN_DEFINED),)
XTRA_CLEAN_DEFINED:=1
.PHONY: xtra_clean
xtra_clean:
	@echo Cleaning $(XTRA_CLEANTARGETS)
	@rm $(XTRA_CLEANTARGETS)

endif

