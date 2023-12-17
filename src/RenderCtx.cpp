#include "Engine/RenderCtx.hpp"
#include "Engine/Geometry.hpp"
#include "spdlog.h"
#include "glm/gtx/transform.hpp"
#include "glad/glad.h"

namespace Engine {
	RenderCtx::RenderCtx() {}

	RenderCtx::~RenderCtx() {
		delete quad;
		delete normalShader;
	}

	void RenderCtx::Init() {
		quad = new Geometry(Geometry::LoadData {
			.vertices = { Geometry::Vertex(glm::vec2 {  0.5f,  0.5f }),
										Geometry::Vertex(glm::vec2 {  0.5f, -0.5f }),
										Geometry::Vertex(glm::vec2 { -0.5f, -0.5f }),
										Geometry::Vertex(glm::vec2 { -0.5f,  0.5f }) },
			.indices = { 0, 1, 3, 1, 2, 3 }
		});
		normalShader = new Shader(Shader::LoadData {
			.vertex_path = "assets/my_shader.vert.glsl",
			.fragment_path = "assets/my_shader.frag.glsl"
		});
	}

	void RenderCtx::DrawRect(glm::vec2 c1, glm::vec2 c2, Color c) {
		normalShader->Bind();
		quad->Bind();

		glDrawElements(GL_TRIANGLES, quad->indexCount, GL_UNSIGNED_INT, 0);

		quad->Unbind();
		normalShader->Unbind();
	}
	// void RenderCtx::DrawTexturedRect(glm::vec2 c1, glm::vec2 c2, std::shared_ptr<Texture> t, Color c) {
	// }
	void RenderCtx::DrawLine(glm::vec2 p1, glm::vec2 p2, Color c) {
	}
	void RenderCtx::DrawCircle(glm::vec2 center, float r, Color c) {
	}
	void RenderCtx::DrawEllipse(glm::vec2 center, float r1, float r2, Color c) {
	}
	void RenderCtx::DebugPush(const std::string& label) {
		std::string blanks(transformStack.size() + 1, '-');
		spdlog::info("{} Push :: {}", blanks, label);
	}
	void RenderCtx::DebugPop(const std::string& label) {
		std::string blanks(transformStack.size() + 1, '-');
		spdlog::info("{} Pop  :: {}", blanks, label);
	}
	void RenderCtx::Push(const std::string& label) {
		RecomputeTransformation();
		if (!label.empty())
			DebugPush(label);
		transformStack.push(activeTransformation);
	}
	void RenderCtx::Pop(const std::string& label) {
		if (transformStack.empty()) {
			spdlog::warn("No push associated with this Pop()");
			return;
		}
		activeTransformation = transformStack.top();
		transformStack.pop();
		if (!label.empty())
			DebugPop(label);
		RecomputeTransformation();
	}
	void RenderCtx::Rotate(float _angle) {
		activeTransformation.angle = _angle;
		RecomputeTransformation();
	}
	void RenderCtx::Scale(glm::vec2 _scale) {
		activeTransformation.scale = glm::vec3(_scale, 1);
		RecomputeTransformation();
	}
	void RenderCtx::Translate(glm::vec2 _translation) {
		activeTransformation.translation = glm::vec3(_translation, 1);
		RecomputeTransformation();
	}
	void RenderCtx::RecomputeTransformation() {
		glm::mat4 model = transformStack.empty() ? glm::mat4(1) : transformStack.top().transform; 		// the transformation to apply the new transformation to
		model = glm::translate(model, activeTransformation.translation);
		model = glm::scale(model, activeTransformation.scale);
		model = glm::rotate(model, glm::radians(activeTransformation.angle), glm::vec3(0, 0, 1));
		activeTransformation.transform = model;
	}
}
