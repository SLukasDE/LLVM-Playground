#include "myclang/helpers/ASTUnit.h"
#include "myclang/astvisitors/ParsedTemplates.h"

#include <memory>
#include <set>
#include <string>

int main(int argc, char const **argv) {
	std::set<std::string> parsedTemplates;

	myclang::helpers::ASTUnit astUnit(argc, argv);
	myclang::astvisitors::ParsedTemplates visitor(parsedTemplates);
	astUnit.run(visitor);

	return 0;
}
