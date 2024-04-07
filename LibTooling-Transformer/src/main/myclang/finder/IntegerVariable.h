#ifndef MYCLANG_FINDER_INTEGERVARIABLE_H_
#define MYCLANG_FINDER_INTEGERVARIABLE_H_

#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Rewrite/Core/Rewriter.h>

namespace myclang {
namespace finder {

class IntegerVariable : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
	explicit IntegerVariable(clang::ASTContext &context);

	void start();
	void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;

private:
	clang::ASTContext &context;
};

} /* namespace finder */
} /* namespace myclang */

#endif /* MYCLANG_FINDER_INTEGERVARIABLE_H_ */
