#include "../Engine/Entity.hpp"

class PlayerEntity : public Entity<PlayerEntity> {
	void Start();
	void Update(double dt);
	void Render(Engine::RenderCtx& ctx);
};
