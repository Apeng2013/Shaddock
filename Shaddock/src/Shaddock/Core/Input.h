#pragma once

#include <glm/glm.hpp>
#include "Shaddock/Core/KeyCodes.h"
#include "Shaddock/Core/MouseCodes.h"

namespace Shaddock {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}