#ifndef MYCLANG_ASTCONSUMERS_NAMEDCLASS_H_
#define MYCLANG_ASTCONSUMERS_NAMEDCLASS_H_

#include "myclang/astvisitors/NamedClass.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

namespace myclang {
namespace astconsumers {

class NamedClass : public clang::ASTConsumer {
public:
	explicit NamedClass(clang::ASTContext& astContext);

	void HandleTranslationUnit(clang::ASTContext& astContext) override;

private:
	astvisitors::NamedClass visitor;
};

} /* namespace astconsumers */
} /* namespace myclang */

#endif /* MYCLANG_ASTCONSUMERS_NAMEDCLASS_H_ */
