#!/bin/sh

#DONE
call_variant_of_classsource () {
    case "$2" in
        "RecursiveASTVisitor")
           build/main/myclang/mains/classsource/RecursiveASTVisitor ./src/resources/test.cc ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

#DONE
call_variant_of_dumper () {
    case "$2" in
        "ASTFrontendAction")
           build/main/myclang/mains/dumper/ASTFrontendAction ;;
        "ToolAction")
           build/main/myclang/mains/dumper/ToolAction ./src/resources/test.cc ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

#DONE
call_variant_of_matchdecls () {
    case "$2" in
        "ToolAction")
           build/main/myclang/mains/matchdecls/ToolAction ./src/resources/User.hpp -- -I. ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

#HALF
call_variant_of_namedclass () {
    case "$2" in
        # ERROR (new)
        "ASTConsumer")
           build/main/myclang/mains/namedclass/ASTConsumer ./src/resources/namedclass.hpp ;;
        # DONE
        "ASTFrontendAction")
           build/main/myclang/mains/namedclass/ASTFrontendAction "namespace n { namespace m { class C {}; } }" ;;
        # DONE
        "RecursiveASTVisitor")
           build/main/myclang/mains/namedclass/RecursiveASTVisitor ./src/resources/namedclass.hpp ;;
        # ERROR (new), but DUMPER and SYNTAXONLYACTION works (syntaxonlyaction is very similar)
        "ToolAction")
           build/main/myclang/mains/namedclass/ToolAction ./src/resources/namedclass.hpp ;;
           # it workes with 'syntaxonlyaction.hpp'
           # build/main/myclang/mains/namedclass/ToolAction ./src/resources/syntaxonlyaction.hpp ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

call_variant_of_parsedtemplates () {
    case "$2" in
        "ASTConsumer")
           build/main/myclang/mains/parsedtemplates/ASTConsumer ./src/resources/test.cpp ;;
        "ASTFrontendAction")
           build/main/myclang/mains/parsedtemplates/ASTFrontendAction ;;
        "RecursiveASTVisitor")
           build/main/myclang/mains/parsedtemplates/RecursiveASTVisitor ;;
        "ToolAction")
           build/main/myclang/mains/parsedtemplates/ToolAction ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

#HALF
call_variant_of_printclasses () {
    case "$2" in
        "ASTConsumer")
           #BROKEN - compare code with old namespace
           build/main/myclang/mains/printclasses/ASTConsumer ./src/resources/test.cc ;;
        "RecursiveASTVisitor")
           #DONE
           build/main/myclang/mains/printclasses/RecursiveASTVisitor ./src/resources/test.cc ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

#DONE
call_variant_of_syntaxonlyaction () {
    case "$2" in
        "ASTFrontendAction")
           build/main/myclang/mains/syntaxonlyaction/ASTFrontendAction ;;
        "ToolAction")
           build/main/myclang/mains/syntaxonlyaction/ToolAction ./src/resources/syntaxonlyaction.hpp ;;
        *)
           echo "Unknown variant $2 for test class $1" ;;
    esac
}

call_testclass () {
    case $1 in
    "classsource")
       call_variant_of_classsource $1 $2 ;;
    "dumper")
       call_variant_of_dumper $1 $2 ;;
    "matchdecls")
       call_variant_of_matchdecls $1 $2 ;;
    "namedclass")
       call_variant_of_namedclass $1 $2 ;;
    "parsedtemplates")
       call_variant_of_parsedtemplates $1 $2 ;;
    "printclasses")
       call_variant_of_printclasses $1 $2 ;;
    "syntaxonlyaction")
       call_variant_of_syntaxonlyaction $1 $2 ;;
    *)
       echo "Unknown test class $1 ." ;;
    esac
}

call_testclass $1 $2
