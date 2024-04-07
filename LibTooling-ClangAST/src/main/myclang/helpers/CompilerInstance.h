#ifndef MYCLANG_HELPERS_COMPILERINSTANCE_H_
#define MYCLANG_HELPERS_COMPILERINSTANCE_H_

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

#include "clang/Frontend/CompilerInstance.h"               // clang::CompilerInstance

#include <string>

namespace myclang {
namespace helpers {

class CompilerInstance {
public:
	CompilerInstance(const std::string& inputFileStr); //"../Clang-Resources/test.cpp"

	clang::ASTContext& getASTContext();
	clang::CompilerInstance& getCompilerInstance();

	void run(clang::ASTConsumer& astConsumer);

private:
	clang::CompilerInstance compilerInstance;
};

} /* namespace helpers */
} /* namespace myclang */

#endif /* MYCLANG_HELPERS_COMPILERINSTANCE_H_ */
