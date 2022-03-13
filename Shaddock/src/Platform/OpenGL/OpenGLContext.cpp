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
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
