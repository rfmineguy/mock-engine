#include <string>


struct Component {};
class Script {
protected:
	template <typename T>
	void AddBehavior() {}
};
class GameObject {
	template <typename T>
	GameObject& WithScript(T script) {
		static_assert(std::is_base_of<Script, T>::value, "Attempted to add script that is not a script");
	}
};
struct Texture {};
struct Vector2 {
	float x,y;
};
struct CollisionInfo {};
struct Engine {
	enum class KeyCode {
		A, D, W, S
	};
	struct Resource {
		static Texture LoadTexture(const std::string&);
		static void UnloadTexture(const Texture&);
	};
	struct Input {
		static bool IsKeyPressed(const KeyCode&);
	};
	struct RenderCtx {
		void DrawTexture(const Texture&, Vector2);
	};
	struct Scene {
		static GameObject& GetGameObject(const std::string&);
	};
};

#include <type_traits>
class Entity : public Script {
	private:
		Texture playerTexture;
		Vector2 position;

	public:
		void Start() {
			playerTexture = Engine::Resource::LoadTexture("player.png");
		}
	

		void End() {
			Engine::Resource::UnloadTexture(playerTexture); 		// could the internals manage this?
		}

		void Update(double dt) {
			if (Engine::Input::IsKeyPressed(Engine::KeyCode::A)) {
				position.x -= 10 * dt;
			}
			if (Engine::Input::IsKeyPressed(Engine::KeyCode::D)) {
				position.x += 10 * dt;
			}
			if (Engine::Input::IsKeyPressed(Engine::KeyCode::W)) {
				position.y += 10 * dt;
			}
			if (Engine::Input::IsKeyPressed(Engine::KeyCode::S)) {
				position.y -= 10 * dt;
			}
		}

		void Render(Engine::RenderCtx& ctx) {
			ctx.DrawTexture(playerTexture, position);
			Engine::Scene::GetGameObject("player");
		}

		void OnCollide(CollisionInfo& c) {
		}
};
