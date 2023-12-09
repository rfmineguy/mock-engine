#ifndef SCENE_H
#define SCENE_H

#include "Engine/ResourceManager.hpp"
#include "RenderCtx.hpp"
#include "Entity.hpp"
#include <memory>
#include <string>
#include "spdlog.h"

namespace Engine {
	class Scene {
	public:
		class Node {
		private:
			std::shared_ptr<IEntity> entity;
			std::shared_ptr<ResourceManager> rm;
		private:
			Node* parent;
			std::vector<Node*> children;

		private:
			Node(std::shared_ptr<ResourceManager> rm): entity(nullptr), parent(nullptr), rm(rm) {} // NOTE: Should only be used as root node
			Node(std::shared_ptr<IEntity> entity, std::shared_ptr<ResourceManager> rm):
				entity(entity), parent(nullptr), children(), rm(rm) {}
			~Node() {
				// spdlog::info("Deleting node");
				for (auto* child : children) {
					delete child;
					child = nullptr;
				}
			}

		public:
			template <typename T>
			void AddChild(const std::string& id) {
				static_assert(std::is_base_of<IEntity, T>::value, "Attempt to add child which is not an entity");
				spdlog::info("Adding child id:{}", id);
				this->children.push_back(new Node(std::make_shared<T>(id, rm), rm));
			}
			friend class Scene; 
		};

	public:
		Scene();
		~Scene();

	private:
		Node* root;
		std::shared_ptr<ResourceManager> resourceManager;

	private:
		Node* GetNodeWithIdRec(Node*, const std::string&) const;
		void PrintSpaces(int) const;
		void TraverseRec(Node*, int) const;
	
	public:
		Node* GetRoot() const;
		Node* GetNodeWithId(const std::string&) const;
		void Traverse() const;

	friend class App;
	};
}

namespace Engine {
}

#endif
