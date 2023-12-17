#ifndef UTIL_HPP
#define UTIL_HPP
#include <string>

namespace Engine {
class Util {
	public:
		static std::string ReadFile(const std::string&);
		static void PrintSpaces(int);
};
}

#endif
