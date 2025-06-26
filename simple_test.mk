## TESTING macros

# $1 = test name/number
# $2 = expected, $3 = result
#
define simpletest
dotest::
	@if [[ '$2' == '$3' ]]; then \
		echo "passed test: $1: '$3'"; \
	else \
	echo "failed test: $1: '$2' != '$3'" 1>&2; \
	fi;

endef

define negativetest
dotest::
	@if [[ '$2' != '$3' ]]; then \
		echo "passed test: $1: '$2' != '$3'"; \
	else \
		echo "failed test: $1: '$2'" 1>&2; \
	fi;

endef
