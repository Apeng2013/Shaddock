#include "sdpch.h"

#include "Shaddock/Core/Application.h"
#include "Shaddock/Core/Input.h"
#include <GLFW/glfw3.h>

namespace Shaddock {

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}
	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
	float Input::GetMouseX()
	{
		glm::vec2 pos = GetMousePosition();
		return pos.x;
	}
	float Input::GetMouseY()
	{
		glm::vec2 pos = GetMousePosition();
		return pos.y;
	}
}