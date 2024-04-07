#include "myclang/helpers/ASTUnit.h"
#include "myclang/astvisitors/NamedClass.h"

#include <memory>

int main(int argc, char const **argv) {
	myclang::helpers::ASTUnit astUnit(argc, argv);
	myclang::astvisitors::NamedClass visitor(astUnit.getASTUnit().getASTContext());
	astUnit.run(visitor);

	return 0;
}
