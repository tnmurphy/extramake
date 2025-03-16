
-load $(XTRA_OUTPUTDIR)/mkdir$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/mkdir$(XTRA_EXT): $(XTRA_OUTPUTDIR)/mkdir.o
	gcc -shared -o $@ $^  

$(XTRA_OUTPUTDIR)/mkdir.o: $(XTRA_SOURCE)/mkdir.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$(XTRA_CLEANTARGETS) \
    $(XTRA_XTRA_OUTPUTDIR)/mkdir$(XTRA_EXT) $(XTRA_XTRA_OUTPUTDIR)/mkdir.o \


