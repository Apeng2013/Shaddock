#include "sdpch.h"
#include "Shaddock/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Shaddock {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None: SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		case RendererAPI::API::OpenGL: return CreateScope<OpenGLRendererAPI>();
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}