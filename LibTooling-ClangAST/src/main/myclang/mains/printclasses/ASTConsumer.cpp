#include "myclang/helpers/CompilerInstance.h"
#include "myclang/astconsumers/PrintClasses.h"

int main(int argc, char const** argv) {
	if (argc <= 1) {
		return -1;
	}

	myclang::helpers::CompilerInstance compilerInstance(argv[1]);
	myclang::astconsumers::PrintClasses astConsumer;
	compilerInstance.run(astConsumer);
	return 0;
}
