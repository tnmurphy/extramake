include xtra.mk

-load $(XTRA_OUTPUTDIR)/reverse$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call simpletest,reverse_letters,d c b a,$(reverse a b c d)))
$(eval $(call simpletest,reverse_tokens_longer_than_one,ef cd ab,$(reverse ab cd ef)))
$(eval $(call simpletest,reverse_empty,,$(reverse)))
$(eval $(call simpletest,reverse_1whitespace,,$(reverse )))
$(eval $(call simpletest,reverse_2whitespace,,$(reverse  )))
$(eval $(call simpletest,reverse_excess_whitespace_middle,ijk efgh abcd,$(reverse abcd       efgh ijk)))
$(eval $(call simpletest,reverse_excess_whitespace_end,ijk efgh abcd,$(reverse abcd       efgh ijk     )))
$(eval $(call simpletest,reverse_excess_whitespace_start,ijk efgh abcd,$(reverse     abcd       efgh ijk)))
