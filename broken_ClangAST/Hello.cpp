#include <iostream>

#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/Casting.h"

#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/Basic/LangOptions.h"
#include "clang/Basic/FileSystemOptions.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Basic/FileManager.h"

#include "clang/Frontend/Utils.h"

#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/Version.h"

#include "clang/Lex/Preprocessor.h"
#include "clang/Frontend/FrontendOptions.h"

#include "clang/Basic/IdentifierTable.h"
#include "clang/Basic/Builtins.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Sema/Sema.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/Type.h"
#include "clang/AST/Decl.h"
#include "clang/Sema/Lookup.h"
#include "clang/Sema/Ownership.h"
#include "clang/AST/DeclGroup.h"

#include "clang/Parse/Parser.h"

#include "clang/Parse/ParseAST.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Rewrite/Frontend/Rewriters.h"

using namespace clang;
using namespace std;

// By implementing RecursiveASTVisitor, we can specify which AST nodes
// we're interested in by overriding relevant methods.
class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor>
{
public:
//  MyASTVisitor() : {} 
//  MyASTVisitor(Rewriter &R)
//      : TheRewriter(R)
//  {}

    bool VisitStmt(clang::Stmt *s) {
//      llvm::errs() << "Visiting statement\n";     
//      if (clang::isa<clang::BinaryOperator>(s)) {
//          if (cast<BinaryOperator>(s)->isAssignmentOp() == true) {
//              // blablabla
//          }
//      }
        return true;
    }

    bool VisitBinaryOperator(BinaryOperator* bo) {
        if (bo->isAssignmentOp() == true) {
            llvm::errs() << "Visiting assignment ";
            Expr *LHS;
            LHS = bo->getLHS();
            DeclRefExpr* dre;
            if ((dre = dyn_cast<DeclRefExpr>(LHS))) { 
                string name = (dre->getNameInfo()).getName().getAsString();
                llvm::errs() << "to " << name;
            }
            if (ArraySubscriptExpr* ase = dyn_cast<ArraySubscriptExpr>(LHS)) { 
                Expr *arrayBase = ase->getBase()->IgnoreParenCasts();
                if ((dre = dyn_cast<DeclRefExpr>(arrayBase))) { 
                    string name = (dre->getNameInfo()).getName().getAsString();
                    llvm::errs() << "to array " << name;
                }
            }
            llvm::errs() << "\n";
        }
        return true;
    }

    bool shouldVisitTemplateInstantiations() const { 
        llvm::errs() << "PIPPOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << "\n";
        return true; }

    bool VisitCXXOperatorCallExprs(CXXOperatorCallExpr *e) {
        llvm::errs() << "Visiting cxxoperatorcall" << "\n";
        return true;
    }

    bool VisitCXXConstructorDecl(CXXConstructorDecl *c) {
        llvm::errs() << "Visiting CXXConstructorDecl" << "\n";
        return true;        
    }

    bool VisitDeclRefExpr(DeclRefExpr* expr) {
        string name = (expr->getNameInfo()).getName().getAsString();
        llvm::errs() << name << "\n";
        return true;
    }

    bool VisitVarDecl(VarDecl *v) {
        llvm::errs() << "Visiting declaration of variable " << v->getDeclName().getAsString() << "\n";
        llvm::errs() << "  type: " << v->getTypeSourceInfo()->getType().getTypePtr()->getTypeClassName();
        if (v->getTypeSourceInfo()->getType().getTypePtr()->isFloatingType() == true) {
            llvm::errs() << " -> float";
        }
        if(v->getTypeSourceInfo()->getType().getTypePtr()->isConstantArrayType() == true) {
            llvm::errs() << " of ";
            llvm::errs() << v->getTypeSourceInfo()->getType().getAsString();
            llvm::errs() << " size ";
            llvm::APInt arraySize = cast<ConstantArrayType>(v->getTypeSourceInfo()->getType().getTypePtr())->getSize();
            llvm::errs() << arraySize;
        }
        if(v->getTypeSourceInfo()->getType().getTypePtr()->isPointerType() == true) {
            llvm::errs() << " to " << v->getTypeSourceInfo()->getType().getAsString();

        }
        llvm::errs() << "\n";
        return true;
    }

  bool VisitTypedefDecl(clang::TypedefDecl *d) {
        llvm::errs() << "Visiting " << d->getDeclKindName() << " " << d->getName() << "\n";

        return true; // returning false aborts the traversal        
    }

    bool VisitFunctionDecl(FunctionDecl *f) {
        llvm::errs() << "Visiting function " << f->getNameInfo().getName().getAsString() << "\n";

        return true;
    }



private:
//  Rewriter &TheRewriter;
};


// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
class MyASTConsumer : public ASTConsumer
{
public:
    MyASTConsumer() : Visitor() {}
//  MyASTConsumer(Rewriter &R)
//      : Visitor(R)
//  {}

    // Override the method that gets called for each parsed top-level
    // declaration.
    virtual bool HandleTopLevelDecl(DeclGroupRef DR) {
        for (DeclGroupRef::iterator b = DR.begin(), e = DR.end();
                 b != e; ++b)
            // Traverse the declaration using our AST visitor.
            Visitor.TraverseDecl(*b);
        return true;
    }

private:
    MyASTVisitor Visitor;
};


int main(int argc, char** argv)
{
    if (argc < 2) {
        llvm::errs() << "Usage: rewritersample <filename> libs\n";
        return 1;
    }

    clang::DiagnosticOptions diagnosticOptions;
    clang::TextDiagnosticPrinter *pTextDiagnosticPrinter =
        new clang::TextDiagnosticPrinter(
            llvm::outs(),
            &diagnosticOptions);
    llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> pDiagIDs;
    clang::DiagnosticsEngine *pDiagnosticsEngine =
        new clang::DiagnosticsEngine(pDiagIDs,
            &diagnosticOptions,
            pTextDiagnosticPrinter);

    clang::LangOptions languageOptions;
    clang::FileSystemOptions fileSystemOptions;
    clang::FileManager fileManager(fileSystemOptions);

    clang::SourceManager sourceManager(
        *pDiagnosticsEngine,
        fileManager);

    llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions> headerSearchOptions(new clang::HeaderSearchOptions());
        headerSearchOptions->ResourceDir = "/opt/llvm_build" "/lib/clang/" CLANG_VERSION_STRING;
    // <Warning!!> -- Platform Specific Code lives here
    // This depends on A) that you're running linux and
    // B) that you have the same GCC LIBs installed that
    // I do.
    // Search through Clang itself for something like this,
    // go on, you won't find it. The reason why is Clang
    // has its own versions of std* which are installed under
    // /usr/local/lib/clang/<version>/include/
    // See somewhere around Driver.cpp:77 to see Clang adding
    // its version of the headers to its include path.
        for (int i = 2; i < argc; i++) {
            headerSearchOptions->AddPath(argv[i],
                                                                     clang::frontend::Angled,
                                                                     false,
                                                                     false);
        }
    // </Warning!!> -- End of Platform Specific Code

    clang::TargetOptions targetOptions;
    targetOptions.Triple = llvm::sys::getDefaultTargetTriple();

    clang::TargetInfo *pTargetInfo =
        clang::TargetInfo::CreateTargetInfo(
            *pDiagnosticsEngine,
            &targetOptions);

    clang::HeaderSearch headerSearch(headerSearchOptions,
                                     fileManager,
                                     *pDiagnosticsEngine,
                                     languageOptions,
                                     pTargetInfo);
    clang::CompilerInstance compInst;

    llvm::IntrusiveRefCntPtr<clang::PreprocessorOptions> pOpts( new clang::PreprocessorOptions());
    clang::Preprocessor preprocessor(
        pOpts,
        *pDiagnosticsEngine,
        languageOptions,
        pTargetInfo,
        sourceManager,
        headerSearch,
        compInst);

    clang::FrontendOptions frontendOptions;
    clang::InitializePreprocessor(
        preprocessor,
        *pOpts,
        *headerSearchOptions,
        frontendOptions);

    const clang::FileEntry *pFile = fileManager.getFile(
        argv[1]);
    sourceManager.createMainFileID(pFile);

    const clang::TargetInfo &targetInfo = *pTargetInfo;

    clang::IdentifierTable identifierTable(languageOptions);
    clang::SelectorTable selectorTable;

    clang::Builtin::Context builtinContext;
    builtinContext.InitializeTarget(targetInfo);
    clang::ASTContext astContext(
        languageOptions,
        sourceManager,
        pTargetInfo,
        identifierTable,
        selectorTable,
        builtinContext,
        0 /* size_reserve*/);
   MyASTConsumer astConsumer;

    clang::Sema sema(
        preprocessor,
        astContext,
        astConsumer);

    pTextDiagnosticPrinter->BeginSourceFile(languageOptions, &preprocessor);
    clang::ParseAST(preprocessor, &astConsumer, astContext);
    pTextDiagnosticPrinter->EndSourceFile();
    return 0;
}
