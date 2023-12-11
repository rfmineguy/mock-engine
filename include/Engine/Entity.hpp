#ifndef ENTITY_H
#define ENTITY_H

#include "RenderCtx.hpp"
#include "ResourceManager.hpp"
#include "spdlog.h"
#include "glm/glm.hpp"
#include <iostream>

namespace Engine {
class IEntity {
	protected:
		std::string id;
		std::shared_ptr<Engine::ResourceManager> resourceManager;

	protected:
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

	protected:
		IEntity(const std::string& id): id(id) {}
		virtual ~IEntity() {
			// spdlog::info("Destroy entity");
		}

	public:
		virtual void Start() = 0;
		virtual void Update(double) = 0;
		virtual void Render(Engine::RenderCtx&) const = 0;
		const std::string& GetID() const { return id; }

	friend class App;
	friend class Scene;
};
}

#endif
