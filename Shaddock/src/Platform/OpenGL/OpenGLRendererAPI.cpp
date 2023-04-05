#include "sdpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Shaddock {

	void OpenGLMessageCallback(unsigned  source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:			SD_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:			SD_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:				SD_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION:	SD_CORE_TRACE(message); return;
		}
		SD_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		SD_PROFILE_FUNCTION();

#ifdef SD_DEBUG
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		if (versionMajor > 4 || (versionMajor == 4 && versionMinor >= 3))
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		}
		else
		{
			SD_CORE_WARN("OpenGLMessageCallback required OpenGL version4.3 at least!");
		}
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);

	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
}