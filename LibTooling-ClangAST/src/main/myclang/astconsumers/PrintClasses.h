#include "myclang/astvisitors/PrintClasses.h"

#include "clang/AST/ASTConsumer.h"                         // clang::ASTConsumer
#include "clang/AST/DeclGroup.h"                           // clang::DeclGroupRef

#include "llvm/Support/raw_ostream.h"                      // llvm::raw_ostream

#ifndef MYCLANG_ASTCONSUMERS_PRINTCLASSES_H_
#define MYCLANG_ASTCONSUMERS_PRINTCLASSES_H_

namespace myclang {
namespace astconsumers {

class PrintClasses : public clang::ASTConsumer {
public:
	PrintClasses();
	bool HandleTopLevelDecl(clang::DeclGroupRef declGroupRef) override;

private:
	astvisitors::PrintClasses astVisitor;
};

} /* namespace astconsumers */
} /* namespace myclang */

#endif /* MYCLANG_ASTCONSUMERS_PRINTCLASSES_H_ */
