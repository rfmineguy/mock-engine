#include "Engine/Geometry.hpp"
#include "glad/glad.h"

namespace Engine {
	Geometry::Geometry(const Geometry::LoadData& loadData)
	: Resource(""), vertexCount(loadData.vertices.size()), indexCount(loadData.indices.size()) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, loadData.vertices.size() * sizeof(Vertex), loadData.vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, loadData.indices.size() * sizeof(unsigned int), loadData.indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Geometry::~Geometry() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	void Geometry::Bind() const {
		glBindVertexArray(vao);
	}

	void Geometry::Unbind() const {
		glBindVertexArray(0);
	}
}
