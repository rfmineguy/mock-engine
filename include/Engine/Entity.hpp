#ifndef ENTITY_H
#define ENTITY_H

#include "RenderCtx.hpp"
#include "spdlog.h"

class IEntity {
	protected:
		std::string id;
	protected:
		IEntity(const std::string& id): id(id) {}
		virtual ~IEntity() {
			spdlog::info("Destroy entity");
		}
	public:
		virtual void Start() = 0;
		virtual void Update(double) = 0;
		virtual void Render(Engine::RenderCtx&) const = 0;
		const std::string& GetID() const { return id; }
	friend class Scene;
};

#endif
