#ifndef VECTOR_H
#define VECTOR_H

namespace Engine {
	// TODO: Maybe just typedef gml::vec2/glm::vec3 as Vector2/Vector3 instead of this craziness
	struct Vector2 {
		float x, y;
		Vector2(): x(0), y(0) {}
		Vector2(float x, float y): x(x), y(y) {}
	};
	struct Vector3 {
		float x, y, z;
		Vector3(): x(0), y(0), z(0) {}
		Vector3(float x, float y, float z): x(x), y(y), z(z) {}
	};
}

#endif
