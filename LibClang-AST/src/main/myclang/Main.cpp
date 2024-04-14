#include "myclang/Main.h"

#include <clang-c/Index.h>

#include <iostream>

namespace myclang {

namespace {
CXChildVisitResult visit(CXCursor cursor, CXCursor, CXClientData) {
	CXCursorKind kind = clang_getCursorKind(cursor);

	// We are looking for functions or methods only
	if (kind == CXCursorKind::CXCursor_FunctionDecl || kind == CXCursorKind::CXCursor_CXXMethod) {
		// The display name is sometimes more descriptive than the spelling name
		// (which is just the source code).
		auto cursorName = clang_getCursorDisplayName(cursor);

		// Print if function/method has 'foo' in it's name
		auto cursorNameString = std::string(clang_getCString(cursorName));
		if (cursorNameString.find("foo") != std::string::npos) {
			// Grab the source range, i.e. (start, end) SourceLocation pair.
			CXSourceRange range = clang_getCursorExtent(cursor);

			// Grab the start of the range.
			CXSourceLocation location = clang_getRangeStart(range);

			// Decompose the SourceLocation into a location in a file.
			CXFile file;
			unsigned int line;
			unsigned int column;
			clang_getFileLocation(location, &file, &line, &column, nullptr);

			// Get the name of the file.
			auto fileName = clang_getFileName(file);

			std::cout << "Found function"
					<< " in " << clang_getCString(fileName)
					<< " at " << line
					<< ":" << column
					<< std::endl;

			// Manual cleanup!
			clang_disposeString(fileName);
		}

		// Manual cleanup!
		clang_disposeString(cursorName);
	}

	return CXChildVisit_Recurse;
}
}

Main::Main() {
}

int Main::run(int argc, const char* argv[]) {
	if (argc < 2) {
		std::cout << "Invalid number of arguments!" << std::endl;
	}
	std::cout << "File to parse: \"" << argv[1] << "\"" << std::endl;

	// Create an index with excludeDeclsFromPCH = 1, displayDiagnostics = 1
	CXIndex index = clang_createIndex(1, 1);

	// Expected arguments:
	// 1) The index to add the translation unit to,
	// 2) The name of the file to parse,
	// 3) A pointer to strings of further command line arguments to compile,
	// 4) The number of further arguments to compile,
	// 5) A pointer to a an array of CXUnsavedFiles structs,
	// 6) The number of CXUnsavedFiles (buffers of unsaved files) in the array,
	// 7) A bitmask of options.
	CXTranslationUnit translationUnit = clang_parseTranslationUnit(
			index,
			argv[1],
			argv + 2,
			argc - 2,
			nullptr,
			0,
			0);
			//CXTranslationUnit_SkipFunctionBodies);  // Speed up parsing by skipping function bodies

	// Visit all the nodes in the AST
	CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);
	clang_visitChildren(cursor, visit, nullptr);

	// Release memory. RAII?
	clang_disposeTranslationUnit(translationUnit);
	clang_disposeIndex(index);

	return 0;
}

} /* namespace myclang */
