#include "myclang/helpers/ASTUnit.h"
#include "myclang/astvisitors/PrintClasses.h"

#include <memory>

int main(int argc, char const **argv) {
	myclang::helpers::ASTUnit astUnit(argc, argv);
	myclang::astvisitors::PrintClasses visitor;
	astUnit.run(visitor);

	return 0;
}
