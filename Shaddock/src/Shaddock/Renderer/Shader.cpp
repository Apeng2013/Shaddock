#include "sdpch.h"
#include "Shader.h"
#include "Shaddock/Renderer/RendererAPI.h"
#include "Shaddock/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Shaddock {
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			SD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		SD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	//ShaderLibrary
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		SD_CORE_ASSERT(!Exits(name), "Shader already exit!");
		m_Shader[name] = shader;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto name = shader->GetName();
		m_Shader[name] = shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		SD_CORE_ASSERT(Exits(name), "Shader not Found!");
		return m_Shader[name];
	}
	bool ShaderLibrary::Exits(const std::string& name) const
	{
		return m_Shader.find(name) != m_Shader.end();
	}
}