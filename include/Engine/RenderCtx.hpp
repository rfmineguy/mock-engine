#ifndef RENDER_CTX_H
#define RENDER_CTX_H
// #include "Vector.hpp"
#include "Color.hpp"
#include "Geometry.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "glm/glm.hpp"
#include <stack>

namespace Engine {
#define BATCH_SIZE 10
	struct Transform {
		float angle;
		glm::vec3 scale, translation;
		glm::mat4 transform;
	};
	class RenderCtx {
	private:
		Geometry* quad;
		Shader *normalShader, *circleShader;
		int width, height;
	private:
		glm::mat4 view, proj;

	private:
		RenderCtx();
		~RenderCtx();
		void Init();

	private:
		Transform activeTransformation;
		std::stack<Transform> transformStack;

	private:
		void RecomputeTransformation();
		void DebugPush(const std::string&);
		void DebugPop(const std::string&);

	public:
		// NOTE: this should be a layered rendering context (1-100) or something
		void DrawRect(glm::vec2 c1, glm::vec2 c2, Color c = Color::White());
		// void DrawTexturedRect(glm::vec2 c1, glm::vec2 c2, std::shared_ptr<Texture> t, Color c = Color::White());
		void DrawLine(glm::vec2 p1, glm::vec2 p2, Color c = Color::White());
		void DrawCircle(glm::vec2 center, float r, Color c = Color::White());
		void DrawEllipse(glm::vec2 center, float r1, float r2, Color c = Color::White());

	public:
		void DrawText(const std::string&, glm::vec2, int, Color c = Color::White());
	public:
		void Push(const std::string&);
		void Pop(const std::string&);
		void Rotate(float);
		void Translate(glm::vec2);
		void Scale(glm::vec2);
	public:
		void UpdateSize(int, int);

	public:
		void RenderBatches() const; // NOTE: For later.
	friend class App;
	};
}
#endif
