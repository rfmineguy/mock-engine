#include "Engine/RenderCtx.hpp"
#include "Engine/Geometry.hpp"
#include "Engine/Shader.hpp"
#include "spdlog.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include <complex>

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
			.fragment_path = "assets/my_shader.frag.glsl",
		});
		circleShader = new Shader(Shader::LoadData {
			.vertex_path = "assets/circle.vert.glsl",
			.fragment_path = "assets/circle.frag.glsl",
		});
	}

	void RenderCtx::DrawRect(glm::vec2 c1, glm::vec2 c2, Color c) {
		normalShader->Bind();
		normalShader->SetUniform4f("uColor", c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
		normalShader->SetUniformMat4("model", activeTransformation.transform);
		normalShader->SetUniformMat4("view", glm::mat4(1));
		circleShader->SetUniformMat4("projection", glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f, -100.f, 100.f));
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
		circleShader->Bind();
		circleShader->SetUniform4f("uColor", c.r, c.g, c.b, c.a);
		circleShader->SetUniformMat4("model", activeTransformation.transform);
		circleShader->SetUniformMat4("view", glm::mat4(1));
		circleShader->SetUniformMat4("projection", glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f, -100.f, 100.f));
		circleShader->SetUniform1f("uRadius", r);
		quad->Bind();
		glDrawElements(GL_TRIANGLES, quad->indexCount, GL_UNSIGNED_INT, 0);
		quad->Unbind();
		circleShader->Unbind();
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
	void RenderCtx::UpdateSize(int width, int height) {
		this->width = width;
		this->height = height;
	}
	void RenderCtx::RecomputeTransformation() {
		glm::mat4 model = transformStack.empty() ? glm::mat4(1) : transformStack.top().transform; 		// the transformation to apply the new transformation to
		model = glm::translate(model, activeTransformation.translation);
		model = glm::scale(model, activeTransformation.scale);
		model = glm::rotate(model, glm::radians(activeTransformation.angle), glm::vec3(0, 0, 1));
		activeTransformation.transform = model;
	}
}
