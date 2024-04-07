#include "myclang/helpers/ASTUnit.h"
#include "myclang/astvisitors/ClassSource.h"

#include <memory>

int main(int argc, char const **argv) {
	myclang::helpers::ASTUnit astUnit(argc, argv);
	myclang::astvisitors::ClassSource visitor(astUnit.getASTUnit());
	astUnit.run(visitor);

	return 0;
}
