#ifndef MYCLANG_TRANSFORMER_FUNCTIONCALLTRANSFORMER_H_
#define MYCLANG_TRANSFORMER_FUNCTIONCALLTRANSFORMER_H_

#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Rewrite/Core/Rewriter.h>

#include <llvm/Support/raw_ostream.h>

#include <set>
#include <string>

namespace myclang {
namespace transformer {

class FunctionCallTransformer : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
	explicit FunctionCallTransformer(clang::ASTContext& context, clang::Rewriter& rewriter);

	void start();
	void run(const clang::ast_matchers::MatchFinder::MatchResult& result) override;
	void print(llvm::raw_ostream& stream);

private:
	clang::ASTContext& context;
	clang::Rewriter& rewriter;

	std::set<std::string> functions;
};

} /* namespace transformer */
} /* namespace myclang */

#endif /* MYCLANG_TRANSFORMER_FUNCTIONCALLTRANSFORMER_H_ */
