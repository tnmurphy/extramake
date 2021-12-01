
-load $(XTRA_OUTPUTDIR)/comp$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/comp$(XTRA_EXT): $(XTRA_OUTPUTDIR)/comp.o
	gcc -shared -o $@ $^  

$(XTRA_OUTPUTDIR)/comp.o: $(XTRA_SOURCE)/comp.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$(XTRA_CLEANTARGETS) \
    $(XTRA_XTRA_OUTPUTDIR)/comp$(XTRA_EXT) $(XTRA_XTRA_OUTPUTDIR)/comp.o \


