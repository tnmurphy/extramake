
-load regex.so

HANDLE:=$(regcomp (b...).*)
$(info HANDLE=$(HANDLE))

$(info RESULT1=$(regexec $(HANDLE),i1235badabcdef))
$(info RESULT2=$(regexec $(HANDLE),bad12869))
$(info RESULT3=$(regexec $(HANDLE),abba))


