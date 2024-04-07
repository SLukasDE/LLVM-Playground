#!/bin/sh

clang++ -I/usr/lib/llvm-10/include/ -I../LibTooling-ClangAST/src/main -Isrc/main/ -fPIC -c src/main/myclang/Plugin.cpp -o build/main/myclang/Plugin.o
clang++ build/main/myclang/Plugin.o -L../LibTooling-ClangAST/build/main -l astvisitors -shared -o build/libMyPlugin.so
