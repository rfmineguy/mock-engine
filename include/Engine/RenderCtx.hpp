#ifndef RENDER_CTX_H
#define RENDER_CTX_H
#include "Vector.hpp"
#include "Color.hpp"
#include "Texture.hpp"

namespace Engine {
	struct RenderCtx {
		// NOTE: this should be a layered rendering context (1-100) or something
		void DrawRect(Vector2 c1, Vector2 c2, Color c = Color::White());
		void DrawTexturedRect(Vector2 c1, Vector2 c2, const Texture& t, Color c = Color::White());
		void DrawLine(Vector2 p1, Vector2 p2, Color c = Color::White());
		void DrawCircle(Vector2 center, float r, Color c = Color::White());
		void DrawEllipse(Vector2 center, float r1, float r2, Color c = Color::White());
	};
}

#endif
