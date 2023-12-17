#include "Engine/Entity.hpp"
#include "Engine/Util.hpp"

namespace Engine {
	IEntity::IEntity(const std::string& id): id(id), parent(nullptr) {}
	IEntity::~IEntity() {
		for (IEntity* e : children) {
			delete e;
		}
	}
	const std::string& IEntity::GetID() const {
		return id;
	}
	const void IEntity::Delete() {
		shouldDelete = true; // defer deletion until a little bit later
	}
	IEntity* IEntity::GetChild(const std::string& id) {
		for (auto* child : children) {
			if (child->GetID() == id) {
				return child;
			}
		}
		return nullptr;
	}
	IEntity* IEntity::GetChild(const int index) {
		if (index < 0 || index > children.size()) {
			return nullptr;
		}
		return children.at(index);
	}
	IEntity* IEntity::GetParent() {
		return parent;
	}
	IEntity* IEntity::GetEntityByID(const std::string& id) {
		// from the root (TODO)
		return GetEntityByIdRec(this, id);
	}
	IEntity* IEntity::GetEntityByIdRec(IEntity* n, const std::string& id) const {
		IEntity* found = nullptr;
		if (n->GetID() == id) {
			return n;
		}
		for (auto* e : n->children) {
			found = GetEntityByIdRec(e, id);
			if (found) break;
		}
		return found;
	}
	void IEntity::Traverse() const {
		std::cout << "Traversing" << std::endl;
		TraverseRec(this, 0);
	}
	void IEntity::TraverseRec(const IEntity* e, int depth) const {
		Util::PrintSpaces(depth);
		if (e == nullptr) {
			return;
		}
		std::cout << e->GetID() << std::endl;
		for (auto* child : e->children) {
			TraverseRec(child, depth + 1);
		}
	}
}
