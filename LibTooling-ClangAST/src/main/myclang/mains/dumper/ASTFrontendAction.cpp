#include "myclang/astfrontendactions/Dumper.h"

#include "clang/Tooling/Tooling.h"

#include <memory>

int main(int, char const **) {
	std::string code = R"V0G0N(// test.cc
// Test for deleted-ctor.exe.

// Explicit ctor, not deleted.
class END {
public:
  END();
};

// Explicit ctor, deleted.
class ED {
public:
  ED()=delete;
};


// Implicit ctor, not deleted.
class IND {
public:
};

// Implicit ctor, deleted.
class ID {
public:
  int &i;
};

// EOF)V0G0N";

	bool rc = clang::tooling::runToolOnCode(std::make_unique<myclang::astfrontendactions::Dumper>(), code.c_str());
	return rc ? 0 : -1;
}
