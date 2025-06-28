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


# Compile flags

# Extended is the default anyhow
extended_HANDLE:=$(regcomp ab(a..),REG_EXTENDED)
$(eval $(call simpletest,match_extended,abada ada,$(regexec $(extended_HANDLE),1abada)))

icase_HANDLE:=$(regcomp bad,REG_ICASE)
$(eval $(call simpletest,match_icase,BAD,$(regexec $(icase_HANDLE),2BAD123)))

# nosub is problematic and possibly not that useful.
# nosub_HANDLE:=$(regcomp ab(a..))
# $(eval $(call simpletest,match_nosub,abada,$(regexec $(nosub_HANDLE),3abada)))

define multiline
4abadabad
xyzzy

endef

newline_HANDLE:=$(regcomp bad.xyz,REG_NEWLINE)
#$(eval $(call simpletest,match_newline,$(multiline),$(regexec $(newline_HANDLE),$(multiline))))

