#!/bin/bash
rm lex.yy.c
rm interp
rm mc
rm y.tab.c
rm y.tab.h

lex comp.l
yacc -d comp.y
g++ lex.yy.c y.tab.c -o mc
./mc < inp.i

gcc interpreter.c -o interp
./interp machine_code
