#pragma once

#include "Core/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Raid {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}