#include "../Engine/Entity.hpp"
#include "Engine/ResourceManager.hpp"

class PlayerEntity : public Engine::IEntity {
private:
	int r;
	float time;
public:
	PlayerEntity(const std::string& id);
	~PlayerEntity();
	void Start() override;
	void Update(double dt) override;
	void Render(Engine::RenderCtx& ctx) const override;
};
