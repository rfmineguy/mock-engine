#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>

namespace Engine {
	class Resource {
		protected:
			std::string resourceId, path;
		protected:
			struct LoadData {
				std::string path;
			};
			Resource(const std::string&);
	};
}

#endif
