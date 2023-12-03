#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

namespace Engine {
	template <typename T>
	void AddResource(const std::string&);

	template <typename T>
	const T& GetResource(const std::string&);
}

#endif
