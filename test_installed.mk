include xtra.mk
load $(XTRA_INSTALLDIR)/hash$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/equals$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/strlen$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/sum$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/mul$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/comp$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/mkdir$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/regex$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/reverse$(XTRA_EXT)
load $(XTRA_INSTALLDIR)/time$(XTRA_EXT)

all::
	@echo "hash abc=$(hash abc)"
	@echo "equals: (equals cat,cat) = '$(equals cat,cat)'"
	@echo "strlen abc=$(strlen abc)"
	@echo "sum: 1+2=$(sum 1 2)"
	@echo "mul: 2*3*4=$(mul 2 3 4)"
	@echo "gt: 100>99=$(gt 100,99)"
	@echo "lt: 100<99=$(lt 100,99)"
	@echo "regexec $(let handle,$(regcomp b.*),$(regexec $(handle), abcd))"


