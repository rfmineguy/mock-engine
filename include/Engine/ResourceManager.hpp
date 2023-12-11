#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "Resource.hpp"
#include "Texture.hpp"
#include "TextureAtlas.hpp"
#include "spdlog.h"

#include <map>
#include <queue>
#include <type_traits>
#include <typeinfo>
#include <memory>

namespace Engine {
	class ResourceManager {
	private:
		struct ResourceEntry {
			std::shared_ptr<Resource> data;
			ResourceEntry(std::shared_ptr<Resource> data): data(data) {}
		};

		std::map<std::string, ResourceEntry> resourceMap;
	public:
		ResourceManager();
		~ResourceManager();

	public:
		template <typename T, typename TData>
		void NewResource(const std::string&, std::function<void(TData&)>);

		template <typename T>
		const std::shared_ptr<T> GetResource(const std::string&) const;

		void Clear();

		int Count() const { return resourceMap.size(); }
	};
}

namespace Engine {
	template <typename T, typename TData>
	void ResourceManager::NewResource(const std::string & id, std::function<void (TData &)> func) {
		static_assert(std::is_base_of<Resource, T>::value, "Attempted to create resource of incorrect form (required to have base of Resource)");
		static_assert(std::is_base_of<Resource::LoadData, TData>::value, "Attempted to create resource with incorrect data class (required to have base of LoadData)");
		TData d;
		func(d);
		resourceMap.emplace(id, ResourceEntry(std::make_shared<T>(d)));
		spdlog::info("New resource registered: {}", id);
	}

	template <typename T>
	const std::shared_ptr<T> ResourceManager::GetResource(const std::string& id) const {
		static_assert(std::is_base_of<Resource, T>::value, "Attempted to retrieve a resource of incorrect form");
		if (resourceMap.find(id) == resourceMap.end()) {
			// spdlog::critical("The resource '{}' has not been registered yet. I'm giving you a null texture.", id);
			return nullptr; //TODO: Give back a default texture
		}
		return std::static_pointer_cast<T, Resource>(resourceMap.at(id).data);
	}
}

#endif
