#include "sdpch.h"
#include "Shaddock/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Shaddock {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}