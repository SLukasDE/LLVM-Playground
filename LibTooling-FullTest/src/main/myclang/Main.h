#ifndef MYCLANG_MAIN_H_
#define MYCLANG_MAIN_H_

#include <string>

namespace myclang {

class Main {
public:
	Main();

	int run(const std::string& filename);
};

} /* namespace myclang */

#endif /* MYCLANG_MAIN_H_ */
