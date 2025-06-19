
-load regex.so

HANDLE:=$(regcomp (b...).*)
$(info HANDLE=$(HANDLE))

$(info RESULT1=$(regexec $(HANDLE),i1235badabcdef)) # badabcdef bada
$(info RESULT2=$(regexec $(HANDLE),bad12869)) # bad12869 bad1
$(info RESULT3=$(regexec $(HANDLE),abba)) # empty
STR:=abad,0987654321
$(info RESULT4=$(regexec $(HANDLE),$(STR)))


