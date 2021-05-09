#include "raidpch.h"
#include "App.h"


namespace Raid {

	#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	static void GLFWErrorCallback(int error, const char* description)
	{
		RAID_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}


	App::~App()
	{
	}

	void App::Run()
	{
		while (m_Running)
		{
			m_Window->Update();
		}
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		RAID_CORE_TRACE("{0}", e);
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}