all: siphash24_test equals_test strlen_test sum_test mul_test comp_test

include allmodules.mk

siphash24_test:
	echo "siphash24-1"; [ "$(siphash24 1234567890)" != "" ] 
	echo "siphash24-2"; [ "$(siphash24 1,12)" == "" ] 
	echo "siphash24-3"; [ "$(siphash24 1234567890)" != "$(siphash24 123456789a)" ] 
	echo "siphash24-4"; [ "$(siphash24 1,123456789abcdef0)" != "" ] 
	echo "siphash24-5"; [ "$(siphash24 1,123456789abcdef1)" != "$(siphash24 1,123456789abcdef3)" ] 
	echo "siphash24-5"; [ "$(siphash24 1,123456789abcdef1)" == "3c17808acefa61ff" ] 

equals_test:
	echo "equals-1"; [ "$(equals ,)" == "" ]
	echo "equals-2"; [ "$(equals a,a)" == "a" ]
	echo "equals-3"; [ "$(equals 11,11)" == "11" ]
	echo "equals-4"; [ "$(equals 11,12)" == "" ]
	echo "equals-5"; [ "$(equals 1 1,1 2)" == "" ]
	echo "equals-6"; [ "$(equals 1 1,1 1)" == "1 1" ]

strlen_test:
	echo "strlen-1"; [ "$(strlen)" == "" ]
	echo "strlen-2"; [ "$(strlen a)" == "1" ]
	echo "strlen-3"; [ "$(strlen 1a)" == "2" ]
	echo "strlen-4"; [ "$(strlen 0987654321 a)" == "12" ]

sum_test:
	echo "sum1"; [ "$(sum 1 1)" == "2" ]
	echo "sum2"; [ "$(sum 1 -1)" == "0" ]
	echo "sum3"; [ "$(sum )" == "0" ]
	echo "sum4"; [ "$(sum 12a 34)" == "" ]
	echo "sum5"; [ "$(sum 12 34b)" == "" ]
	echo "sum6"; [ "$(sum 1 2 3 4)" == "10" ]
	echo "sum7"; [ "$(sum 1 -50)" == "-49" ]
	echo "sum8"; [ "$(sum        1	    -9)" == "-8" ]

mul_test:
	echo "mul1"; [ "$(mul 1 1)" == "1" ]
	echo "mul2"; [ "$(mul 1 -1)" == "-1" ]
	echo "mul3"; [ "$(mul 1 0)" == "0" ]
	echo "mul4"; [ "$(mul 12a 34)" == "" ]
	echo "mul5"; [ "$(mul 12 34b)" == "" ]
	echo "mul6"; [ "$(mul 2 2 3 4)" == "48" ]
	echo "mul7"; [ "$(mul )" == "" ]
	echo "mul8 (overflow)"; [ "$(mul 1000000 1000000 1000000 1000000 1000000 1000000)" != "1000000000000000000000000000000000000" ]

comp_test:
	echo "comp1"; [ "$(lt 1,2)" == "1" ]
	echo "comp2"; [ "$(lt 1,1)" == "" ]
	echo "comp3"; [ "$(gt 2,1)" == "1" ]
	echo "comp4"; [ "$(gt 1,3)" == "" ]
	echo "comp5"; [ "$(gte 3,3)" == "1" ]
	echo "comp6"; [ "$(gte 3,4)" == "" ]
	echo "comp7"; [ "$(lte 4,3)" == "" ]
	echo "comp8"; [ "$(lte 4,4)" == "1" ]
	echo "comp9"; [ "$(lte ,)" == "" ]
	echo "comp10"; [ "$(lt ,)" == "" ]
	echo "comp11"; [ "$(gt 1,)" == "" ]
	echo "comp12"; [ "$(gt ,1)" == "" ]

clean:
	rm -f $(XTRA_CLEANTARGETS)
