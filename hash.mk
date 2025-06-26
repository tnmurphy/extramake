include simple_module.mk

$(eval $(call moduleplus,hash,siphash24))

test::
	valgrind --track-origins=yes make -f test_hash.mk

