#pragma once

#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/KeyCodes.h"
#include "Shaddock/Core/MouseCodes.h"

namespace Shaddock {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static Scope<Input> Create();

	protected:
		Input() = default;
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	public:
		virtual ~Input() = default;
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

	private:
		static Scope<Input> s_Instance;
	};
}