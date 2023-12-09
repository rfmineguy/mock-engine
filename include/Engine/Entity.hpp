#ifndef ENTITY_H
#define ENTITY_H

#include "RenderCtx.hpp"
#include "ResourceManager.hpp"
#include "spdlog.h"

class IEntity {
	protected:
		std::string id;
		std::shared_ptr<Engine::ResourceManager> resourceManager;
	protected:
		IEntity(const std::string& id, std::shared_ptr<Engine::ResourceManager> rm): id(id), resourceManager(rm) {}
		virtual ~IEntity() {
			// spdlog::info("Destroy entity");
		}
	public:
		virtual void Start() = 0;
		virtual void Update(double) = 0;
		virtual void Render(Engine::RenderCtx&) const = 0;
		const std::string& GetID() const { return id; }
	friend class Scene;
	friend class Node;
};

#endif
