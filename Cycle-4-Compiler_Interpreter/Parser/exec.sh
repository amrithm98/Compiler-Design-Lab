!#/bin/bash
lex comp.l
yacc -d comp.y
gcc lex.yy.c y.tab.c
./a.out < inp.i
