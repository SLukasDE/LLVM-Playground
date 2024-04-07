#!/bin/sh

# main
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/main.cpp -o build/main/main.o
clang++ -L/usr/lib/llvm-10/lib build/main/main.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/main


# ClassSource
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/classsource/RecursiveASTVisitor.cpp -o build/main/myclang/mains/classsource/RecursiveASTVisitor.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/classsource/RecursiveASTVisitor.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/classsource/RecursiveASTVisitor


# Dumper
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/dumper/ASTFrontendAction.cpp -o build/main/myclang/mains/dumper/ASTFrontendAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/dumper/ASTFrontendAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/dumper/ASTFrontendAction

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/dumper/ToolAction.cpp -o build/main/myclang/mains/dumper/ToolAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/dumper/ToolAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/dumper/ToolAction


# MatchDecls
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/matchdecls/ToolAction.cpp -o build/main/myclang/mains/matchdecls/ToolAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/matchdecls/ToolAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/matchdecls/ToolAction


# NamedClass
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/namedclass/ASTConsumer.cpp -o build/main/myclang/mains/namedclass/ASTConsumer.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/namedclass/ASTConsumer.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/namedclass/ASTConsumer

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/namedclass/ASTFrontendAction.cpp -o build/main/myclang/mains/namedclass/ASTFrontendAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/namedclass/ASTFrontendAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/namedclass/ASTFrontendAction

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/namedclass/RecursiveASTVisitor.cpp -o build/main/myclang/mains/namedclass/RecursiveASTVisitor.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/namedclass/RecursiveASTVisitor.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/namedclass/RecursiveASTVisitor

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/namedclass/ToolAction.cpp -o build/main/myclang/mains/namedclass/ToolAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/namedclass/ToolAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/namedclass/ToolAction


# ParsedTemplates
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/parsedtemplates/ASTConsumer.cpp -o build/main/myclang/mains/parsedtemplates/ASTConsumer.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/parsedtemplates/ASTConsumer.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/parsedtemplates/ASTConsumer

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/parsedtemplates/ASTFrontendAction.cpp -o build/main/myclang/mains/parsedtemplates/ASTFrontendAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/parsedtemplates/ASTFrontendAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/parsedtemplates/ASTFrontendAction

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/parsedtemplates/RecursiveASTVisitor.cpp -o build/main/myclang/mains/parsedtemplates/RecursiveASTVisitor.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/parsedtemplates/RecursiveASTVisitor.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/parsedtemplates/RecursiveASTVisitor

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/parsedtemplates/ToolAction.cpp -o build/main/myclang/mains/parsedtemplates/ToolAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/parsedtemplates/ToolAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/parsedtemplates/ToolAction


# PrintClasses
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/printclasses/ASTConsumer.cpp -o build/main/myclang/mains/printclasses/ASTConsumer.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/printclasses/ASTConsumer.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/printclasses/ASTConsumer

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/printclasses/RecursiveASTVisitor.cpp -o build/main/myclang/mains/printclasses/RecursiveASTVisitor.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/printclasses/RecursiveASTVisitor.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/printclasses/RecursiveASTVisitor


# SyntaxOnlyAction
clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/syntaxonlyaction/ASTFrontendAction.cpp -o build/main/myclang/mains/syntaxonlyaction/ASTFrontendAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/syntaxonlyaction/ASTFrontendAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/syntaxonlyaction/ASTFrontendAction

clang++ -I/usr/lib/llvm-10/include -I src/main -c src/main/myclang/mains/syntaxonlyaction/ToolAction.cpp -o build/main/myclang/mains/syntaxonlyaction/ToolAction.o
clang++ -L/usr/lib/llvm-10/lib build/main/myclang/mains/syntaxonlyaction/ToolAction.o -Lbuild/main -lastvisitors -lclang-cpp -lLLVM-10 -o build/main/myclang/mains/syntaxonlyaction/ToolAction
