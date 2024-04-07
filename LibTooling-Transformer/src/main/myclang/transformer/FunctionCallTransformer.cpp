#include "myclang/transformer/FunctionCallTransformer.h"

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/ASTMatchers/ASTMatchers.h>


namespace myclang {
namespace transformer {

FunctionCallTransformer::FunctionCallTransformer(clang::ASTContext& aContext, clang::Rewriter& aRewriter)
: context(aContext),
  rewriter(aRewriter)
{ }

void FunctionCallTransformer::start() {
	clang::ast_matchers::MatchFinder functionFinder;

	auto callExprMatcher = clang::ast_matchers::callExpr().bind("callExpr");
	functionFinder.addMatcher(callExprMatcher, this);

	functionFinder.matchAST(context);
}

void FunctionCallTransformer::run(const clang::ast_matchers::MatchFinder::MatchResult& result) {
	/*
	 * CallExpr is the function call
	 * FunctionDecl is fhe function definition
	*/

	if(const clang::CallExpr *callExpr = result.Nodes.getNodeAs<clang::CallExpr>("callExpr")) {
		if(const clang::FunctionDecl *function = callExpr->getDirectCallee()) {
			if(result.SourceManager->isInSystemHeader(function->getSourceRange().getBegin())) {
				return;
			}

			auto functionName = function->getNameAsString();
			rewriter.InsertTextAfter(callExpr->getBeginLoc(), "fn_");

			if (functions.count(functionName) == 0) {
				// rewrite definition as well
				rewriter.InsertTextAfter(function->getLocation(), "fn_");
				functions.insert(function->getNameAsString());
			}
		}
	}
}

void FunctionCallTransformer::print(llvm::raw_ostream& stream) {
	for(auto &fn : functions) {
		stream << fn << "(..)\n";
	}
}

} /* namespace transformer */
} /* namespace myclang */
