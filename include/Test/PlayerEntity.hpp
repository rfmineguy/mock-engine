#include "../Engine/Entity.hpp"
#include "Engine/ResourceManager.hpp"

class PlayerEntity : public IEntity {
public:
	PlayerEntity(const std::string& id, std::shared_ptr<Engine::ResourceManager>);
	~PlayerEntity();
	void Start() override;
	void Update(double dt) override;
	void Render(Engine::RenderCtx& ctx) const override;
};
