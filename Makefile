# the modules are attached to the "all" target so here we make it the top level target
.PHONY: all
all::

.PHONY: clean test valgrind do_tests xtra_clean
clean: xtra_clean

# requires valgrind to be installed.
# Runs the test in a submake to allow valgrind to check the process.
test:: valgrind

valgrind:
	if [ -z $$(command -v valgrind) ]; then echo "Valgrind must be installed to test for memory corruption errors."; exit 1; else exit 0; fi

include allmodules.mk
