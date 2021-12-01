
-load $(XTRA_OUTPUTDIR)/hash$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/hash$(XTRA_EXT): $(XTRA_OUTPUTDIR)/hash.o $(XTRA_OUTPUTDIR)/siphash24.o
	gcc -shared -o $@ $^  

$(XTRA_OUTPUTDIR)/hash.o: $(XTRA_SOURCE)/hash.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

$(XTRA_OUTPUTDIR)/siphash24.o: $(XTRA_SOURCE)/siphash24.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$(XTRA_CLEANTARGETS) \
    $(XTRA_XTRA_OUTPUTDIR)/hash$(XTRA_EXT) $(XTRA_XTRA_OUTPUTDIR)/hash.o \
    $(XTRA_XTRA_OUTPUTDIR)/siphash24.o


