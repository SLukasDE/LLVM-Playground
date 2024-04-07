#include "myclang/astfrontendactions/SyntaxOnlyAction.h"

#include "clang/Tooling/Tooling.h"

#include <memory>

int main(int, char const **) {
	bool rc = clang::tooling::runToolOnCode(std::make_unique<myclang::astfrontendactions::SyntaxOnlyAction>(), "class X{a};");
	return rc ? 0 : -1;
}
