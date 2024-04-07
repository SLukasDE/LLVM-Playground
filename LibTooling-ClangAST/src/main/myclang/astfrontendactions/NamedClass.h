#ifndef MYCLANG_ASTFRONTENDACTIONS_NAMEDCLASS_H_
#define MYCLANG_ASTFRONTENDACTIONS_NAMEDCLASS_H_

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"

#include "llvm/ADT/StringRef.h"

#include <memory>

namespace myclang {
namespace astfrontendactions {

class NamedClass : public clang::ASTFrontendAction {
public:
	std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compilerInstance, llvm::StringRef inFile) override;
};

} /* namespace astfrontendactions */
} /* namespace myclang */

#endif /* MYCLANG_ASTFRONTENDACTIONS_NAMEDCLASS_H_ */
