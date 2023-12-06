#ifndef ENTITY_H
#define ENTITY_H

#include "RenderCtx.hpp"

template <typename T>
class Entity {
	virtual void Start() = 0;
	virtual void Update(double) = 0;
	virtual void Render(Engine::RenderCtx&) const = 0;
};

#endif
