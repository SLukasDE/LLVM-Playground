#ifndef MYCLANG_ASTCONSUMER_H_
#define MYCLANG_ASTCONSUMER_H_

#include <clang/AST/ASTContext.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/Rewrite/Core/Rewriter.h>

namespace myclang {

class ASTConsumer : public clang::ASTConsumer {
public:
	explicit ASTConsumer(clang::ASTContext& context);

	virtual void HandleTranslationUnit(clang::ASTContext& context) override;

private:
	clang::Rewriter rewriter;
};

} /* namespace myclang */

#endif /* MYCLANG_ASTCONSUMER_H_ */
