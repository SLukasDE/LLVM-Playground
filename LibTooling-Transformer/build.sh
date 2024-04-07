#!/bin/sh

#Original code: https://github.com/firolino/clang-tool/tree/master

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/main.cpp                                        -o build/main/main.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Action.cpp                              -o build/main/Action.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/ASTConsumer.cpp                         -o build/main/ASTConsumer.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/finder/IntegerVariable.cpp              -o build/main/IntegerVariable.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/Helper.cpp                              -o build/main/Helper.o
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/transformer/FunctionCallTransformer.cpp -o build/main/FunctionCallTransformer.o



# main
clang++ -L/usr/lib/llvm-10/lib \
  build/main/main.o \
  build/main/Action.o \
  build/main/ASTConsumer.o \
  build/main/IntegerVariable.o \
  build/main/Helper.o \
  build/main/FunctionCallTransformer.o \
  -lclang-cpp -lLLVM-10 -o transformer
