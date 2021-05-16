#include "raidpch.h"
#include "App.h"

#include <glad/glad.h>

namespace Raid {

#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App* App::m_Instance = nullptr;

	App::App()
	{
		RAID_CORE_ASSERT(!m_Instance, "App already exists!");
		m_Instance = this;

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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		RAID_CORE_TRACE("{0}", e);

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();) {
			(*--i)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}