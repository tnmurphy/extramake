include xtra.mk

-load $(XTRA_OUTPUTDIR)/sum$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call simpletest,sum_nothing,0,$(sum 0)))
$(eval $(call simpletest,sum_1,1,$(sum 1)))
$(eval $(call simpletest,sum_2,3,$(sum 1 2)))
$(eval $(call simpletest,sum_primes,59,$(sum 1 2 3 5 7 11 13 17)))
$(eval $(call simpletest,sum_negative,-1,$(sum 1 -2)))
$(eval $(call simpletest,sum_zero,0,$(sum -1 1)))
$(eval $(call simpletest,sum_spaces_and_tab,59,$(sum 1 2     3   5 7 11   13 	17)))
