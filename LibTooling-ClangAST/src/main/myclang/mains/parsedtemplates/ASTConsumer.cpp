#include "myclang/helpers/CompilerInstance.h"
#include "myclang/astconsumers/ParsedTemplates.h"

#include <set>
#include <string>

int main(int argc, char const** argv) {
	if (argc <= 1) {
		return -1;
	}

	myclang::helpers::CompilerInstance compilerInstance(argv[1]);
	std::set<std::string> parsedTemplates;

	myclang::astconsumers::ParsedTemplates astConsumer(compilerInstance.getCompilerInstance(), parsedTemplates);
	compilerInstance.run(astConsumer);
	return 0;
}
