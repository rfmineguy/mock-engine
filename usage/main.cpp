#include "common.hpp"

int main() {
	Scene s = Engine::NewScene();
	GameObject o = s.NewGameObject("player").WithScript<Enity>();
	o.AddComponent<Transform>();
	o.AddScript<Entity>();
	s.Run();
}
