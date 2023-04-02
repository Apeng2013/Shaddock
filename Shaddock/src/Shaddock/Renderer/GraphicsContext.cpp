#include "sdpch.h"
#include "Shaddock/Renderer/GraphicsContext.h"
#include "Shaddock/Renderer/Renderer.h"
#include "Shaddock/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "GLFW/glfw3.h"

namespace Shaddock {
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None : SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL : return CreateScope<OpenGLContext>(static_cast<GLFWwindow*> (window));
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}