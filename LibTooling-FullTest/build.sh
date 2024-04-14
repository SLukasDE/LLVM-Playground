#!/bin/sh

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/main.cpp -o build/main/main.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Main.cpp -o build/main/myclang/Main.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Decl.cpp -o build/main/myclang/Decl.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/CompilerInstance.cpp -o build/main/myclang/CompilerInstance.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/QualType.cpp -o build/main/myclang/QualType.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Stmt.cpp -o build/main/myclang/Stmt.o

clang++ -L/usr/lib/llvm-10/lib build/main/myclang/CompilerInstance.o build/main/myclang/Decl.o build/main/myclang/QualType.o build/main/myclang/Stmt.o build/main/myclang/Main.o build/main/main.o -lclang-cpp -lLLVM-10 -o build/main/main
