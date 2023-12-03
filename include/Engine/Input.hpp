#ifndef INPUT_H
#define INPUT_H

namespace Engine {
	struct Input {
		enum class KeyCode {};
		static bool IsKeyDown(char);
		static bool IsKeyDown(KeyCode);
		static bool IsKeyPressed(char);
		static bool IsKeyPressed(KeyCode);
		static bool IsKeyReleased(char);
		static bool IsKeyReleased(KeyCode);
	};
}

#endif
