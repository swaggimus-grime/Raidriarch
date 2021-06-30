#include "raidpch.h"
#include "App.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Raid/Renderer/Renderer.h"
#include "Raid/Core/Timestep.h"

namespace Raid {

	App* App::s_Instance = nullptr;

	App::App()
	{
		RAID_PROFILE_FUNCTION();

		RAID_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	App::~App()
	{
		RAID_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void App::Run()
	{
		while (m_Running)
		{
			float time = glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(App::OnWindowResize));

		RAID_CORE_TRACE("{0}", e);

		for (auto i = m_LayerStack.rbegin(); i != m_LayerStack.rend(); i++) {
			(*i)->OnEvent(e);
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

	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}