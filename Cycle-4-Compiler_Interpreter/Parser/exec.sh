#!/bin/bash
lex comp.l
yacc -d comp.y
g++ lex.yy.c y.tab.c
./a.out < inp.i
