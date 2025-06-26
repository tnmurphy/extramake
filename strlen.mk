include simple_module.mk

$(eval $(call simplemodule,strlen))

test::
	valgrind --track-origins=yes make -f test_strlen.mk





