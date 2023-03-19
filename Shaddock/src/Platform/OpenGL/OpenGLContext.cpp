#include "sdpch.h"
#include "OpenGLContext.h"

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
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SD_CORE_ASSERT(status, "Failed to initialize Glad!");

		SD_CORE_INFO("OpenGL Information:");
		SD_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		SD_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		SD_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		SD_CORE_INFO("	Major Version: {0}", versionMajor);
		SD_CORE_INFO("	Minor Version: {0}", versionMinor);
#ifdef SD_ENABLE_ASSERTS
		SD_CORE_ASSERT(versionMajor > 3 || (versionMajor == 3 && versionMinor >= 3), "Shaddock requires at least OpenGL version 3.3!");
#endif
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
