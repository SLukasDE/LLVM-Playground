#!/bin/sh

clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/ast_matchers/MatchDecls.cpp -o build/main/myclang/ast_matchers/MatchDecls.o

clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astconsumers/NamedClass.cpp      -o build/main/myclang/astconsumers/NamedClass.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astconsumers/ParsedTemplates.cpp -o build/main/myclang/astconsumers/ParsedTemplates.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astconsumers/PrintClasses.cpp    -o build/main/myclang/astconsumers/PrintClasses.o

clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astfrontendactions/Dumper.cpp          -o build/main/myclang/astfrontendactions/Dumper.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astfrontendactions/NamedClass.cpp      -o build/main/myclang/astfrontendactions/NamedClass.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astfrontendactions/ParsedTemplates.cpp -o build/main/myclang/astfrontendactions/ParsedTemplates.o

clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astvisitors/ClassSource.cpp     -o build/main/myclang/astvisitors/ClassSource.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astvisitors/NamedClass.cpp      -o build/main/myclang/astvisitors/NamedClass.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astvisitors/ParsedTemplates.cpp -o build/main/myclang/astvisitors/ParsedTemplates.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/astvisitors/PrintClasses.cpp    -o build/main/myclang/astvisitors/PrintClasses.o

clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/helpers/ASTUnit.cpp          -o build/main/myclang/helpers/ASTUnit.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/helpers/ClangTool.cpp        -o build/main/myclang/helpers/ClangTool.o
clang++ -I/usr/lib/llvm-10/include -I src/main -fPIC -c src/main/myclang/helpers/CompilerInstance.cpp -o build/main/myclang/helpers/CompilerInstance.o


ar rs build/main/libastvisitors.a \
 build/main/myclang/ast_matchers/MatchDecls.o \
 build/main/myclang/astconsumers/NamedClass.o \
 build/main/myclang/astconsumers/ParsedTemplates.o \
 build/main/myclang/astconsumers/PrintClasses.o \
 build/main/myclang/astfrontendactions/Dumper.o \
 build/main/myclang/astfrontendactions/NamedClass.o \
 build/main/myclang/astfrontendactions/ParsedTemplates.o \
 build/main/myclang/astvisitors/ClassSource.o \
 build/main/myclang/astvisitors/NamedClass.o \
 build/main/myclang/astvisitors/ParsedTemplates.o \
 build/main/myclang/astvisitors/PrintClasses.o \
 build/main/myclang/helpers/ASTUnit.o \
 build/main/myclang/helpers/ClangTool.o \
 build/main/myclang/helpers/CompilerInstance.o


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
