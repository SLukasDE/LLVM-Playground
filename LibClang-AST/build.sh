#!/bin/sh

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/main.cpp -o build/main/main.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Main.cpp -o build/main/myclang/Main.o

clang++ -L/usr/lib/llvm-10/lib build/main/myclang/Main.o build/main/main.o -lclang-10 -o build/main/main
