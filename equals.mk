
-load $(XTRA_OUTPUTDIR)/equals$(XTRA_EXT)

$(XTRA_OUTPUTDIR)/equals$(XTRA_EXT): $(XTRA_OUTPUTDIR)/equals.o
	gcc -shared -o $@ $^  

$(XTRA_OUTPUTDIR)/equals.o: $(XTRA_SOURCE)/equals.c
	gcc $(XTRA_CFLAGS) -c $^ -o $@ -I $(XTRA_MAKEHEADERS)

XTRA_CLEANTARGETS:=$(XTRA_CLEANTARGETS) \
    $(XTRA_XTRA_OUTPUTDIR)/equals$(XTRA_EXT) $(XTRA_XTRA_OUTPUTDIR)/equals.o 
