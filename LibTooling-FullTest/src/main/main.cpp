#include "myclang/Main.h"

#include "llvm/Support/CommandLine.h"

static llvm::cl::opt<std::string> fileName(llvm::cl::Positional, llvm::cl::desc("Input file"), llvm::cl::Required);


int main(int argc, char const **argv) {
	llvm::cl::ParseCommandLineOptions(argc, argv, "My full test\n");

	myclang::Main main;
	main.run(fileName);

	return 0;
}
