#!/bin/sh

clang++ -Xclang -load -Xclang ./build/libMyPlugin.so -Xclang -plugin -Xclang print-fns -Xclang -plugin-arg-print-fns -Xclang wurst1 -Xclang -plugin-arg-print-fns -Xclang wurst2 ../LibTooling-ClangAST/src/resources/test.cc
#clang++ -Xclang -load -Xclang ./build/libMyPlugin.so -Xclang -plugin -Xclang print-fns -Xclang -plugin-arg-print-fns -Xclang help  ../LibTooling-ClangAST/src/resources/test.cc
