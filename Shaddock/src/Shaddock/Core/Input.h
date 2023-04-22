#pragma once

#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/KeyCodes.h"
#include "Shaddock/Core/MouseCodes.h"

namespace Shaddock {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}