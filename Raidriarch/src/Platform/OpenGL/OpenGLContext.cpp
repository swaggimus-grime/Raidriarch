#include "raidpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Raid {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RAID_CORE_ASSERT(windowHandle, "Window handle is null!");

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RAID_CORE_ASSERT(status, "Failed to initialize Glad!");

		RAID_CORE_INFO("OpenGL Info:");
		RAID_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		RAID_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		RAID_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
