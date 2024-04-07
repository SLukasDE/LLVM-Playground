#include "myclang/astfrontendactions/ParsedTemplates.h"

#include "clang/Frontend/FrontendPluginRegistry.h"

namespace myclang {

static clang::FrontendPluginRegistry::Add<myclang::astfrontendactions::ParsedTemplates> X("print-fns", "print function names");

} /* namespace myclang */
