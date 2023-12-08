#include "../Engine/Entity.hpp"

class PlayerEntity : public IEntity {
public:
	PlayerEntity(const std::string& id);
	~PlayerEntity();
	void Start() override;
	void Update(double dt) override;
	void Render(Engine::RenderCtx& ctx) const override;
};
