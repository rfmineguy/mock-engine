#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "Resource.hpp"
#include "Texture.hpp"
#include "TextureAtlas.hpp"
#include "spdlog.h"

#include <map>
#include <typeinfo>
#include <memory>

namespace Engine {
	namespace Internal {
		struct ResourceEntry {
			std::shared_ptr<Resource> data;

			ResourceEntry(std::shared_ptr<Resource> data): data(data) {}
		};
		static std::map<std::string, ResourceEntry> resources;
	}

	template <typename T, typename... Args>
	void AddResource(const std::string&, const std::string&);

	template <typename T>
	const T& GetResource(const std::string&);
}

namespace Engine {
	template <typename T, typename... Args>
	void AddResource(const std::string& id, const std::string &filepath) {
		static_assert(std::is_base_of<Resource, T>::value, "Attempted to create resource of incorrect form (required to be base of Resource)");
		spdlog::info("Adding resource id:{}, from:'{}'", id, filepath);

		std::shared_ptr<Resource> resource = std::make_shared<T>();
		resource->Load(filepath);
		Internal::ResourceEntry e = Internal::ResourceEntry(resource);

		Engine::Internal::resources.emplace(id, e);
	}

	template <typename T>
	const T& GetResource(const std::string& id) {
		spdlog::info("Getting resource with id:{}", id);
	}
}


#endif
