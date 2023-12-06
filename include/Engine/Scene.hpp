#ifndef SCENE_H
#define SCENE_H
#include "RenderCtx.hpp"
#include "Entity.hpp"
#include <string>
#include "spdlog.h"

namespace Engine {
	class Scene {
	private:
	public:
		// template <typename T>
		// void AddEntity(
		// 	const std::string& id,
		// 	std::function<void (T&)> start,
		// 	std::function<void (T &, double)> update,
		// 	std::function<void (T &, RenderCtx &)> render); 

		template <typename T>
		void AddEntity(const std::string& id);
	};

}

namespace Engine {
	template <typename T>
	void Scene::AddEntity(
		const std::string& id,
		std::function<void (T&)> start,
		std::function<void (T &, double)> update,
		std::function<void (T &, RenderCtx &)> render) 
	{
		spdlog::info("Adding entity '{}'", id);
	}

	template <typename T>
	void Scene::AddEntity(const std::string& id) {
		static_assert(std::is_base_of<Entity<T>, T>::value, "Attempted to create entity from class of incorrected form (required to have base of Entity)");
		spdlog::info("Adding entity '{}' via class", id);
	}
}

#endif
