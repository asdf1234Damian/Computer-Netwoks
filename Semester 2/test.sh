#!/usr/bin/env bash
# echo "compilando!"
g++ Lab1.cpp -l pthread -o a.out
# echo "Compilado!"
./a.out ${BASH_ARGV[0]}
