#include "myclang/astconsumers/NamedClass.h"

namespace myclang {
namespace astconsumers {

NamedClass::NamedClass(clang::ASTContext& astContext)
: visitor(astContext)
 { }

void NamedClass::HandleTranslationUnit(clang::ASTContext& astContext) {
	visitor.TraverseDecl(astContext.getTranslationUnitDecl());
}

} /* namespace astconsumers */
} /* namespace myclang */
