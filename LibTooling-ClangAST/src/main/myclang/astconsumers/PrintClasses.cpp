#include "myclang/astconsumers/PrintClasses.h"

namespace myclang {
namespace astconsumers {

PrintClasses::PrintClasses()
: astVisitor()
{ }

bool PrintClasses::HandleTopLevelDecl(clang::DeclGroupRef declGroupRef) {
	for (clang::DeclGroupRef::iterator b = declGroupRef.begin(), e = declGroupRef.end(); b != e; ++b) {
		astVisitor.TraverseDecl(*b);
	}
	return true;
}

} /* namespace astconsumers */
} /* namespace myclang */
