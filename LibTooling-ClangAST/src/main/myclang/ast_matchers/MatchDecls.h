#ifndef MYCLANG_AST_MATCHERS_MATCHDECLS_H_
#define MYCLANG_AST_MATCHERS_MATCHDECLS_H_

#include "clang/ASTMatchers/ASTMatchFinder.h" // clang::ast_matchers::MatchFinder , clang::ast_matchers::MatchFinder::MatchResult
#include "clang/AST/Decl.h"                   // clang::FieldDecl, clang::FunctionDecl
#include "clang/AST/DeclCXX.h"                // clang::CXXRecordDecl
#include "clang/Tooling/Tooling.h"

#include <memory>

namespace myclang {
namespace ast_matchers {

class MatchDecls {
public:
	MatchDecls(bool showDetails);

	clang::tooling::FrontendActionFactory& getToolAction();

private:

	class MatchCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
	public:
		MatchCallback(bool showDetails);

		void run(clang::ast_matchers::MatchFinder::MatchResult const& result) override;
		void onStartOfTranslationUnit() override;
		void onEndOfTranslationUnit() override;

	private:
		bool showDetails = false;

		void foundRecord(const clang::CXXRecordDecl& record);
		void foundField(const clang::FieldDecl& field);
		void foundFunction(const clang::FunctionDecl& function);
	};


	MatchCallback callback;

	clang::ast_matchers::DeclarationMatcher classMatcher;
	clang::ast_matchers::DeclarationMatcher propertyMatcher;
	clang::ast_matchers::DeclarationMatcher functionMatcher;
	clang::ast_matchers::MatchFinder finder;
	std::unique_ptr<clang::tooling::FrontendActionFactory> toolAction;
};

} /* namespace ast_matchers */
} /* namespace myclang */

#endif /* MYCLANG_AST_MATCHERS_MATCHDECLS_H_ */
