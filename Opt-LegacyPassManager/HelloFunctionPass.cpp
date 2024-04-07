#include "llvm/IR/Function.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

namespace {

class Hello : public llvm::FunctionPass {
public:
	static char ID;

	Hello() : llvm::FunctionPass(ID) {}

	bool runOnFunction(llvm::Function &function) override {
		llvm::errs() << "Hello: ";
		llvm::errs().write_escaped(function.getName()) << '\n';

		llvm::errs() << "Hello: " << function.getName() << " / " << function.getAlignment() << '\n';
		return false;
	}
}; // end of struct Hello

}  // end of anonymous namespace

char Hello::ID = 0;
static llvm::RegisterPass<Hello> X("hello", "Hello World Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
