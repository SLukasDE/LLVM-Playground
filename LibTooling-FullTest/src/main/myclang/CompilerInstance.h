#ifndef MYCLANG_COMPILERINSTANCE_H_
#define MYCLANG_COMPILERINSTANCE_H_

#include "clang/AST/ASTConsumer.h"                  // clang::ASTConsumer
#include "clang/Frontend/CompilerInstance.h"               // clang::CompilerInstance

#include <string>

namespace myclang {

class CompilerInstance : public clang::CompilerInstance {
public:
	CompilerInstance(bool isCplusplus = true);

	void setSourceCode(const std::string& sourceCode);
	void setSourceFile(const std::string& sourceFile);

//	void run1(clang::ASTConsumer& astConsumer);
//	void run2(clang::ASTConsumer& astConsumer);
};

} /* namespace myclang */

#endif /* MYCLANG_COMPILERINSTANCE_H_ */
