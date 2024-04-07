#include "myclang/astconsumers/NamedClass.h"
#include "myclang/astfrontendactions/NamedClass.h"

namespace myclang {
namespace astfrontendactions {

std::unique_ptr<clang::ASTConsumer> NamedClass::CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef inFile) {
	return std::make_unique<astconsumers::NamedClass>(compilerInstance.getASTContext());
}

} /* namespace astfrontendactions */
} /* namespace myclang */
