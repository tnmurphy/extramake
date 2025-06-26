
include xtra.mk

-load $(XTRA_OUTPUTDIR)/equals$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call simpletest,equals_nothing,1,$(equals ,)))
$(eval $(call simpletest,equals_1char,a,$(equals a,a)))
$(eval $(call simpletest,notequals_1char,,$(equals a,b)))
$(eval $(call simpletest,notequals_1char_nothing,,$(equals a,)))
$(eval $(call simpletest,notequals_1char_nothing,,$(equals ,b)))
$(eval $(call simpletest,equals_multi_char,abcd,$(equals abcd,abcd)))
$(eval $(call simpletest,equals_multi_char_space,ab cd,$(equals ab cd,ab cd)))
$(eval $(call simpletest,not_equals_multi_char_space,,$(equals ab ef,ab cd)))
$(eval $(call simpletest,not_equals_untrimmed,,$(equals ab ,ab)))

