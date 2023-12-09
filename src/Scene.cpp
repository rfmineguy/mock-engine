#include "Engine/Scene.hpp"
#include <iostream>

namespace Engine {
	Scene::Scene(): root(new Scene::Node()) {
	
	}
	Scene::~Scene() {
		delete root;
		root = nullptr;
	}
	Scene::Node* Scene::GetRoot() const {
		return root;
	}
	Scene::Node* Scene::GetNodeWithIdRec(Scene::Node* n, const std::string& id) const {
		Scene::Node* found = nullptr;
		
		if (n->entity && n->entity->GetID() == id) {
			spdlog::info("{}", n->entity->GetID());
			return n;  // Base case
		}
		if (n->children.size() == 0) {
			return nullptr; // Base case
		}
		for (int i = 0; i < n->children.size(); i++) {
			found = GetNodeWithIdRec(n->children.at(i), id);
			if (found) {
				break;
			}
		}
		return found;
	}

	Scene::Node* Scene::GetNodeWithId(const std::string& id) const {
		return GetNodeWithIdRec(GetRoot(), id);
	}

	void Scene::PrintSpaces(int count) const {
		for (int i = 0; i < count; i++) {
			std::cout << "   ";
		}
		std::cout << "\\_";
	}

	void Scene::TraverseRec(Scene::Node* node, int depth) const {
		PrintSpaces(depth);
		if (node == nullptr) { // doesnt happen
			std::cout << "NULL" << std::endl;
			return;
		}
		if (node->entity == nullptr) {
			std::cout << "ROOT" << std::endl;
		}
		else {
			std::cout << node->entity->GetID() << std::endl;
		}
		for (auto* child : node->children) {
			TraverseRec(child, depth + 1);
		}
	}

	void Scene::Traverse() const {
		spdlog::info("Traverse Scene");
		TraverseRec(GetRoot(), 0);
	}
}
