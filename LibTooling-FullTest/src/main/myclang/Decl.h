#ifndef MYCLANG_DECL_H_
#define MYCLANG_DECL_H_

#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/AST/Decl.h"

#include <string>

namespace myclang {

class Decl final {
public:
	Decl() = delete;

	static void dump(clang::Decl& decl, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions);
};

} /* namespace myclang */

#endif /* MYCLANG_DECL_H_ */
