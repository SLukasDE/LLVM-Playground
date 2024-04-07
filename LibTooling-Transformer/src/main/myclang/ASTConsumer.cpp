#include "myclang/ASTConsumer.h"
#include "myclang/finder/IntegerVariable.h"
#include "myclang/transformer/FunctionCallTransformer.h"

#include <llvm/Support/raw_ostream.h>

namespace myclang {

ASTConsumer::ASTConsumer(clang::ASTContext& context) {
}

void ASTConsumer::HandleTranslationUnit(clang::ASTContext& context) {
	rewriter.setSourceMgr(context.getSourceManager(), context.getLangOpts());

	myclang::transformer::FunctionCallTransformer functionCallTransformer(context, rewriter);

	functionCallTransformer.start();
	functionCallTransformer.print(llvm::outs());

	myclang::finder::IntegerVariable intFinder(context);
	intFinder.start();

	auto buffer = rewriter.getRewriteBufferFor(context.getSourceManager().getMainFileID());

	if(buffer) {
		llvm::outs() << "// Buffer exists!\n";
		buffer->write(llvm::outs());
	}
	else {
		llvm::outs() << "No buffer\n";
	}
}

} /* namespace myclang */
