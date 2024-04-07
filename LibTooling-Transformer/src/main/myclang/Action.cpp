#include "myclang/Action.h"
#include "myclang/ASTConsumer.h"

namespace myclang {

std::unique_ptr<clang::ASTConsumer> Action::CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef inFile) {
	return std::unique_ptr<clang::ASTConsumer>(new myclang::ASTConsumer(compiler.getASTContext()));
}


} /* namespace myclang */
