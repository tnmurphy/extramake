-load regex.so

include simple_test.mk

# tests
HANDLE:=$(regcomp (b...).*)
$(info HANDLE=$(HANDLE))

$(eval $(call simpletest,match_substring_2_matches,badabcdef bada,$(regexec $(HANDLE),i1235badabcdef)))
$(eval $(call simpletest,match_substring_1,bad12869 bad1,$(regexec $(HANDLE),bad12869)))
$(eval $(call simpletest,match_too_short,,$(regexec $(HANDLE),abba)))

STR:=abad,0987654321
EXPECTED:=bad,0987654321 bad,
$(eval $(call simpletest,match_commas,$(EXPECTED),$(regexec $(HANDLE),$(STR))))


