include xtra.mk

-load $(XTRA_OUTPUTDIR)/time$(XTRA_EXT)

include simple_test.mk

# tests 
$(eval $(call negativetest,time_hhmmss,,$(time %Y-%m-%dT%H:%M:%SZ)))

# there is a low chance that this one could fail:
$(eval $(call simpletest,time_hhmmss,$(time %Y-%m-%dT%H:%MZ),$(time %Y-%m-%dT%H:%MZ)))

$(eval $(call negativetest,time_hhmmss,$(time %Y-%m-%dT%H:%M:%SZ),$(sleep 1)$(time %Y-%m-%dT%H:%M:%SZ)))

# this one depends on the shell being a unix one which isn't great for windows:
$(eval $(call simpletest,time_hhmmss,$(shell date  +%Y-%m-%dT%H:%MZ),$(time %Y-%m-%dT%H:%MZ)))

# fairly high chance of failing, also unix specific:
$(eval $(call simpletest,time_hhmmss,$(shell date +%Y-%m-%dT%H:%M:%SZ),$(time +)))
