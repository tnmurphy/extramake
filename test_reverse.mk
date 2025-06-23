
-load reverse.so
$(info reverse 'a b c d = $(reverse a b c d))
$(info reverse 'ab cd ef = '$(reverse ab cd ef)')
$(info reverse of nothing = '$(reverse )')
$(info reverse 'abcd       efgh ijk' = '$(reverse abcd       efgh ijk)')


