#  Common definitions

# Linux/unix for now:
XTRA_EXT=.so

XTRA_INCLUDE_VERSION=$(subst .,,$(MAKE_VERSION))
XTRA_MAKEHEADERS ?= ./include/gmake$(XTRA_INCLUDE_VERSION)
XTRA_OUTPUTDIR ?= .
XTRA_CFLAGS ?= -fPIC -O2 -g -Wall -Wextra -Werror
XTRA_SOURCE ?= .
XTRA_INSTALLDIR ?= /usr/lib/extramake/$(file < version)
