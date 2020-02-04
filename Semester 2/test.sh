#!/usr/bin/env bash
# echo "compilando!"
g++ Practica2.cpp -l pthread -o a.out
# echo "Compilado!"
./a.out ${BASH_ARGV[0]}