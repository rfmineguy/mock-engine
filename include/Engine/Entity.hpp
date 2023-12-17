#ifndef ENTITY_H
#define ENTITY_H

#include "RenderCtx.hpp"
#include "ResourceManager.hpp"
#include "spdlog.h"
#include "glm/glm.hpp"
#include <iostream>

namespace Engine {
class Scene;
class IEntity {
	// Scene management stuff
	private:
		IEntity* parent;
		std::vector<IEntity*> children;
		bool shouldDelete;

	// Scene management stuff
	private:
		void TraverseRec(const IEntity*, int) const;
		IEntity* GetEntityByIdRec(IEntity*, const std::string&) const;

	public:
		const void Delete();
		IEntity* GetChild(const std::string&);
		IEntity* GetChild(const int);
		IEntity* GetParent();
		IEntity* GetEntityByID(const std::string&);
		const std::string& GetID() const;
		void Traverse() const;

		template <typename T>
		void AddChild(const std::string& id) {
			static_assert(std::is_base_of<IEntity, T>::value, "Attempt to add child which is not an entity");
			IEntity* e = new T(id);
			e->resourceManager = resourceManager;
			e->Start();
			children.push_back(e);
			spdlog::info("Added entity {}", id);
		}

	// Entity specific accessors
	protected:
		std::string id;
		std::shared_ptr<Engine::ResourceManager> resourceManager;
		std::shared_ptr<Engine::Scene> scene;

	// Entity transformation
	protected:
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

	// RAII
	protected:
		IEntity(const std::string&);
		virtual ~IEntity();

	// Entity lifecycle stuff
	public:
		virtual void Start() = 0;
		virtual void Update(double) = 0;
		virtual void Render(Engine::RenderCtx&) const = 0;

	friend class App;
	friend class Scene;
};
}

#endif
