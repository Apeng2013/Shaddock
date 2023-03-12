#include "sdpch.h"
#include "Shader.h"
#include "Shaddock/Renderer/RendererAPI.h"
#include "Shaddock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Shaddock {
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}