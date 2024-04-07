#include "myclang/astconsumers/ParsedTemplates.h"
#include "myclang/astvisitors/ParsedTemplates.h"

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Sema/Sema.h"
//#include "clang/AST/AST.h"

#include "llvm/Support/raw_ostream.h"

namespace myclang {
namespace astconsumers {

ParsedTemplates::ParsedTemplates(clang::CompilerInstance& aCompilerInstance, std::set<std::string> aParsedTemplates)
: compilerInstance(aCompilerInstance),
  parsedTemplates(aParsedTemplates)
{ }

bool ParsedTemplates::HandleTopLevelDecl(clang::DeclGroupRef declGroupRef) {
	for(clang::DeclGroupRef::iterator i = declGroupRef.begin(), e = declGroupRef.end(); i != e; ++i) {
		const clang::Decl* d = *i;
		if (const clang::NamedDecl *nd = clang::dyn_cast<clang::NamedDecl>(d)) {
			llvm::errs() << "top-level-decl: \"" << nd->getNameAsString() << "\"\n";
		}
	}

	return true;
}

void ParsedTemplates::HandleTranslationUnit(clang::ASTContext& astContext) {
	if (!compilerInstance.getLangOpts().DelayedTemplateParsing) {
		return;
	}

	// This demonstrates how to force instantiation of some templates in
	// -fdelayed-template-parsing mode. (Note: Doing this unconditionally for
	// all templates is similar to not using -fdelayed-template-parsig in the
	// first place.)
	// The advantage of doing this in HandleTranslationUnit() is that all
	// codegen (when using -add-plugin) is completely finished and this can't
	// affect the compiler output.
	astvisitors::ParsedTemplates recursiveASTVisitor(parsedTemplates);

	recursiveASTVisitor.TraverseDecl(astContext.getTranslationUnitDecl());

	clang::Sema& sema = compilerInstance.getSema();
	for (const clang::FunctionDecl* functionDecl : recursiveASTVisitor.getLateParsedDecls()) {
		clang::LateParsedTemplate& lpt = *sema.LateParsedTemplateMap.find(functionDecl)->second;
		sema.LateTemplateParser(sema.OpaqueParser, lpt);
		llvm::errs() << "late-parsed-decl: \"" << functionDecl->getNameAsString() << "\"\n";
    }
}

} /* namespace astconsumers */
} /* namespace myclang */
