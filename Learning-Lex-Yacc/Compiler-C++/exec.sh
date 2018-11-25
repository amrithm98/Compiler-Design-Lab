#!/bin/bash
yacc -d parser.y
lex rules.l
g++ lex.yy.c y.tab.c -o machine_code
./machine_code < input.txt > output.txt
cat output.txt