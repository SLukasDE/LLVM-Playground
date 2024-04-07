#include "myclang/astfrontendactions/Dumper.h"

#include "clang/AST/ASTDumperUtils.h"
#include "clang/Frontend/ASTConsumers.h"

namespace myclang {
namespace astfrontendactions {

std::unique_ptr<clang::ASTConsumer> Dumper::CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef inFile) {
	return clang::CreateASTDumper(
			nullptr,            /* dump to stdout */
			"",                 /* no filter */
			true,               /* dump decls */
			true,               /* deserialize */
			false,              /* don't dump lookups */
			clang::ADOF_Default /* default instead of json */
			);
}

} /* namespace astfrontendactions */
} /* namespace myclang */
