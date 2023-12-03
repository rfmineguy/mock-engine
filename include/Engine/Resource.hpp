#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

namespace Engine {
	template <typename T>
	class Resource {
	public:
		virtual T Load(const std::string&) const = 0;
	};
}
#endif
