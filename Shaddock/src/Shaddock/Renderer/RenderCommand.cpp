#include "sdpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Shaddock {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}