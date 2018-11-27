#!/bin/bash

rm lex.yy.c
rm y.tab.c
rm y.tab.h
yacc -d conv.y
lex conv.l
gcc lex.yy.c y.tab.c
