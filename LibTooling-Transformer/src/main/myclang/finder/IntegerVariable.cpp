#include "myclang/finder/IntegerVariable.h"

#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>

#include <llvm/Support/raw_ostream.h>

namespace myclang {
namespace finder {

IntegerVariable::IntegerVariable(clang::ASTContext& aContext)
: context(aContext)
{ }

void IntegerVariable::start() {
	clang::ast_matchers::MatchFinder integerFinder;

	auto intVarMatcher = clang::ast_matchers::varDecl(clang::ast_matchers::hasType(clang::ast_matchers::isInteger())).bind("intVar");
	integerFinder.addMatcher(intVarMatcher, this);
	integerFinder.matchAST(context);
}

void IntegerVariable::run(const clang::ast_matchers::MatchFinder::MatchResult &result) {
	if(const clang::VarDecl *varDecl = result.Nodes.getNodeAs<clang::VarDecl>("intVar")) {
		if(result.SourceManager->isInSystemHeader(varDecl->getSourceRange().getBegin())) {
			return;
		}

		auto intVarName = varDecl->getNameAsString();
		if (intVarName.empty()) {
			return;
		}

		llvm::outs() << "integer variable: " << varDecl->getNameAsString() << "\n";
    }
}

} /* namespace finder */
} /* namespace myclang */
