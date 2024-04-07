#ifndef MYCLANG_ACTION_H_
#define MYCLANG_ACTION_H_

#include <clang/AST/ASTConsumer.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>

#include <llvm/ADT/StringRef.h>

#include <memory>

namespace myclang {

class Action : public clang::ASTFrontendAction {
public:
	virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef inFile) override;
};

} /* namespace myclang */

#endif /* MYCLANG_ACTION_H_ */
