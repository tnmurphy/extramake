-load hash.so

include simple_test.mk

# tests 
$(eval $(call simpletest,hash_something,58581edcbbc4c2cb,$(hash 1234567890)))
$(eval $(call simpletest,hash_something_else,383a8831bf79431b,$(hash 1234567890a)))
$(eval $(call simpletest,hash_nothing,,$(hash)))
$(eval $(call negativetest,hashes_differ,$(hash 1234566890),$(hash 1234567890)))
