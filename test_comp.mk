include xtra.mk

-load $(XTRA_OUTPUTDIR)/comp$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call simpletest,gt_nothing,,$(gt ,)))
$(eval $(call simpletest,lt_nothing,,$(lt ,)))
$(eval $(call simpletest,gte_nothing,,$(gte ,)))
$(eval $(call simpletest,lte_nothing,,$(lte ,)))

$(eval $(call simpletest,gt_1_0,1,$(gt 1,0)))
$(eval $(call simpletest,gt_1_0_spaces,1,$(gt 1  ,  0  )))
$(eval $(call simpletest,gt_0_1,,$(gt 0,1)))
$(eval $(call simpletest,gt_1_1,,$(gt 1,1)))
$(eval $(call simpletest,gt_0__1,1,$(gt 0,-1)))

$(eval $(call simpletest,lt_1_0,,$(lt 1,0)))
$(eval $(call simpletest,lt_0_1,1,$(lt 0,1)))
$(eval $(call simpletest,lt_0_1_spaces,1,$(lt 0 , 1  ))) 
$(eval $(call simpletest,lt_1_1,,$(lt 1,1)))
$(eval $(call simpletest,lt__1_0,1,$(lt -1,0)))

$(eval $(call simpletest,gte_1_0,1,$(gte 1,0)))
$(eval $(call simpletest,gte_1_0_spaces,1,$(gte 1  ,  0  )))
$(eval $(call simpletest,gte_0_1,,$(gte 0,1)))
$(eval $(call simpletest,gte_1_1,1,$(gte 1,1)))
$(eval $(call simpletest,gte_0__1,1,$(gte 0,-1)))

$(eval $(call simpletest,lte_1_0,,$(lte 1,0)))
$(eval $(call simpletest,lte_0_1,1,$(lte 0,1)))
$(eval $(call simpletest,lte_0_1_spaces,1,$(lte 0 , 1  ))) 
$(eval $(call simpletest,lte_1_1,1,$(lte 1,1)))
$(eval $(call simpletest,lte__1_0,1,$(lte -1,0)))
