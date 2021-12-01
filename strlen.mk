
-load $(XTRA_OUTPUTDIR)/strlen$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/strlen$(XTRA_EXT): $(XTRA_OUTPUTDIR)/strlen.o
	gcc -shared -o $@ $^  

$(XTRA_OUTPUTDIR)/strlen.o: $(XTRA_SOURCE)/strlen.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$(XTRA_CLEANTARGETS) \
    $(XTRA_XTRA_OUTPUTDIR)/strlen$(XTRA_EXT) $(XTRA_XTRA_OUTPUTDIR)/strlen.o \


