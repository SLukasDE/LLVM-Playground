#include "myclang/astfrontendactions/ParsedTemplates.h"

#include "clang/Tooling/Tooling.h"

#include <memory>

int main(int, char const **) {
	std::string code = "...";

	bool rc = clang::tooling::runToolOnCode(std::make_unique<myclang::astfrontendactions::ParsedTemplates>(), code.c_str());
	return rc ? 0 : -1;
}
