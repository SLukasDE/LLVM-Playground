#ifndef MYCLANG_QUALTYPE_H_
#define MYCLANG_QUALTYPE_H_

#include "clang/AST/Type.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"

#include <string>

namespace myclang {

class QualType final {
public:
	QualType() = delete;

	static void dump(const clang::QualType& qualType, std::size_t d, clang::SourceManager& sourceManager, const clang::LangOptions& langOptions);
};

} /* namespace myclang */

#endif /* MYCLANG_QUALTYPE_H_ */
