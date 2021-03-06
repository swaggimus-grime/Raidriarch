#include "raidpch.h"
#include "WindowsWindow.h"

#include "Raid/Events/AppEvent.h"
#include "Raid/Events/MouseEvent.h"
#include "Raid/Events/KeyEvent.h"

#include <vulkan/vulkan.h>
#include "Raid/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"

namespace Raid {

	static bool s_GLFWInitialized = false;

	Scope<Window> Window::Create(const WindowProps& props) {
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	Raid::WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			RAID_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback([](int error, const char* desc) {
					RAID_CORE_ERROR("GLFW ERROR ({0}): {1}", error, desc);
				});
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    
				RAID_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				break;
			case RendererAPI::API::OpenGL:  
				m_Context = new OpenGLContext(m_Window);
				break;
			case RendererAPI::API::Vulkan:  
				m_Context = new VulkanContext(GetRequiredVulkanExtensions());
				break;
			default:
				RAID_CORE_ASSERT(false, "Unknown RendererAPI!");
				break;
		}

		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			}
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		m_Context->SwapBuffers();
		glfwPollEvents();
	} 

	unsigned int WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}
	unsigned int WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	std::vector<const char*>& WindowsWindow::GetRequiredVulkanExtensions()
	{
		uint32_t glfwExtensionCount;
		const char** glfwExtensionNames;
		glfwExtensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		static std::vector<const char*> extensions(glfwExtensionNames, glfwExtensionNames + glfwExtensionCount);

#ifdef RAID_DEBUG
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		return extensions;
	}
}