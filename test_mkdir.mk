
include xtra.mk

-load $(XTRA_OUTPUTDIR)/mkdir$(XTRA_EXT)

include simple_test.mk

TEST_MKDIR_DIR:=$(TMPDIR)/extramake/test/mkdir/1
X:=$(shell rmdir '$(TEST_MKIDIR_DIR)')
# tests 
$(eval $(call simpletest,mkdir_a_dir_with_path,,$(mkdir $(TEST_MKDIR_DIR))))
