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
		struct ResourceManager {
			static ResourceManager& Instance() {
				static ResourceManager r;
				return r;
			}
			static std::map<std::string, ResourceEntry>& resources() {
				return Instance().resourceMap;
			}
			private:
			std::map<std::string, ResourceEntry> resourceMap;
		};
	}

	template <typename T, typename... Args>
	void AddResource(const std::string&, const std::string&, Args... args);

	template <typename T>
	const std::shared_ptr<T> GetResource(const std::string&);

	// NEW API
	template <typename T, typename TData>
	void NewResource(const std::string&, std::function<void(TData&)>);

	static void FreeResources();
}

namespace Engine {
	template <typename T, typename... Args>
	void AddResource(const std::string& id, const std::string &filepath, Args... args) {
		static_assert(std::is_base_of<Resource, T>::value, "Attempted to create resource of incorrect form (required to have base of Resource)");

		std::shared_ptr<Resource> resource = std::make_shared<T>(filepath);
		Internal::ResourceEntry e = Internal::ResourceEntry(resource);

		Engine::Internal::ResourceManager::resources().emplace(id, e);
	}

	template <typename T>
	const std::shared_ptr<T> GetResource(const std::string& id) {
		static_assert(std::is_base_of<Resource, T>::value, "Attempted to retrieve a resource of incorrect form");
		auto& resourceMap = Engine::Internal::ResourceManager::resources();
		if (resourceMap.find(id) == resourceMap.end()) {
			spdlog::critical("The resource '{}' has not been registered yet. I'm giving you a null texture.", id);
			return nullptr; //TODO: Give back a default texture
		}
		auto resource = Engine::Internal::ResourceManager::resources().at(id);
		return std::static_pointer_cast<T, Resource>(Engine::Internal::ResourceManager::resources().at(id).data);
	}

	template <typename T, typename TData>
	void NewResource(const std::string& id, std::function<void (TData&)> func) {
		TData d;
		func(d);
		std::shared_ptr<Resource> resource = std::make_shared<T>(d);
		Internal::ResourceEntry e = Internal::ResourceEntry(resource);

		Engine::Internal::ResourceManager::resources().emplace(id, e);
	}

	void FreeResources() {
		spdlog::info("Clearing the resource pool. {}", Engine::Internal::ResourceManager::resources().size());
		Engine::Internal::ResourceManager::resources().clear();
	}
}

#endif
