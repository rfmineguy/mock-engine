#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include "Resource.hpp"
#include "glm/gtx/transform.hpp"

namespace Engine {
class Geometry : public Resource {
public:
	struct Vertex {
		glm::vec3 position;

		Vertex(glm::vec2 p): position(p, 0) {}
	};
private:
	unsigned int vbo, ebo, vao;
	unsigned int vertexCount, indexCount;

public:
	struct LoadData : public Resource::LoadData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};
public:
	Geometry(const Geometry::LoadData&);
	~Geometry();
	void Bind() const;
	void Unbind() const;
friend class RenderCtx;
};
}

#endif
