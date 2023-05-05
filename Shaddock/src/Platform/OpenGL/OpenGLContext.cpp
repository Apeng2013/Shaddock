#include "sdpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"


namespace Shaddock {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		SD_CORE_ASSERT(windowHandle, "Window handle is Null!");
	}
	void OpenGLContext::Init()
	{
		SD_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SD_CORE_ASSERT(status, "Failed to initialize Glad!");

		SD_CORE_INFO("OpenGL Information:");
		SD_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		SD_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		SD_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
		int versionMajor = GLVersion.major;
		int versionMinor = GLVersion.minor;
		SD_CORE_INFO("Major Version: {0}", versionMajor);
		SD_CORE_INFO("Minor Version: {0}", versionMinor);
		SD_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Shaddock requires at least OpenGL version 3.3!");
	}
	void OpenGLContext::SwapBuffers()
	{
		SD_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}
