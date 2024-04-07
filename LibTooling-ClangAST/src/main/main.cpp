#include "llvm/Support/CommandLine.h"           // llvm::cl::OptionCategory, llvm::cl::extrahelp

#include <iostream>
#include <string>

llvm::cl::opt<std::string> testClass("test-class", llvm::cl::desc("Specify the test"), llvm::cl::value_desc("test class"), llvm::cl::Required);
llvm::cl::opt<std::string> testNamespace("test-namespace", llvm::cl::desc("Specify the namespace of the test if it is not unique"), llvm::cl::value_desc("astconsumers|astfrontendactions|astvisitors"));
llvm::cl::opt<std::string> testRunner("test-runner", llvm::cl::desc("Specify the runner to use if it is not unique"), llvm::cl::value_desc("ASTUnit|ClangTool|RunToolOnCode|CompilerInstance"));
llvm::cl::opt<std::string> testCode("test-code", llvm::cl::desc("Specify the code to use for the test-class if required"), llvm::cl::value_desc("class X{a};"));


int main(int argc, char const **argv) {
	llvm::cl::ParseCommandLineOptions(argc, argv);

	std::cout << "test-class: \"" << testClass << "\"\n";
	std::cout << "test-namespace: \"" << testNamespace << "\"\n";
	return 0;
}
