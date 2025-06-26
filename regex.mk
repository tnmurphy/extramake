include simple_module.mk

$(eval $(call simplemodule,regex))

test::
	valgrind --track-origins=yes make -f test_regex.mk


