#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

namespace Engine {
	class Resource {
	public:
		virtual void Load(const std::string&) const = 0;
	};
}

#endif
