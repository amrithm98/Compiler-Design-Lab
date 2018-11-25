#!/bin/bash
rm a.out
rm y.tab.c
rm y.tab.h
rm lex.yy.c
rm machine_code

yacc -d parser.y
lex rules.l
g++ lex.yy.c y.tab.c  -o machine_code
./machine_code < input.txt > output.txt
cat output.txt

g++ interpreter.cpp -o interpreter
./interpreter machinecode.txt