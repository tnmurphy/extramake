-load strlen.so

include simple_test.mk

# tests 

$(eval $(call simpletest,strlen_noparam,,$(strlen)))

$(eval $(call simpletest,strlen_nothing,0,$(strlen )))
EMPTY:=
$(eval $(call simpletest,strlen_nothing_var,0,$(strlen $(EMPTY))))
$(eval $(call simpletest,strlen_something,5,$(strlen 12345)))
$(eval $(call simpletest,strlen_onechar,1,$(strlen 1)))

SPACE:=$(EMPTY) $(EMPTY)
STR:=$(SPACE)1$(SPACE)
$(eval $(call simpletest,strlen_spaces,3,$(strlen STR)))
