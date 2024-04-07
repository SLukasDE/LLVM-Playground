#include "myclang/astfrontendactions/NamedClass.h"

#include "clang/Tooling/Tooling.h"

#include <memory>

int main(int argc, char const** argv) {
	if (argc > 1) {
		bool rc = clang::tooling::runToolOnCode(std::make_unique<myclang::astfrontendactions::NamedClass>(), argv[1]);
		return rc ? 0 : -1;
	}
	return -1;
}
