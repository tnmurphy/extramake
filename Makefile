# the modules are attached to the "all" target so here we make it the top level target
.PHONY: all
all::

.PHONY: clean
clean: xtra_clean


include allmodules.mk
