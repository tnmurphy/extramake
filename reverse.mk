include simple_module.mk

$(eval $(call simplemodule,reverse))

test::
	valgrind --track-origins=yes make -f test_reverse.mk
