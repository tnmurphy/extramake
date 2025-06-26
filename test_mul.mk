include xtra.mk

-load $(XTRA_OUTPUTDIR)/mul$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call simpletest,mul_nothing,0,$(mul 0)))
$(eval $(call simpletest,mul_1,1,$(mul 1)))
$(eval $(call simpletest,mul_2,6,$(mul 2 3)))
$(eval $(call simpletest,mul_primes,510510,$(mul 1 2 3 5 7 11 13 17)))
$(eval $(call simpletest,mul_negative,-2,$(mul -1 2)))
$(eval $(call simpletest,mul_zero,0,$(mul 1 0)))
$(eval $(call simpletest,mul_spaces_and_tab,510510,$(mul 1 2     3   5 7 11   13 	17)))
