#!/bin/sh

clang++ HelloFunctionPass.cpp -shared -fPIC -o libHello.so
clang hello.c -emit-llvm -c -o hello.bc
opt -load ./libHello.so -hello -time-passes < hello.bc
