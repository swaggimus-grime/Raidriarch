#pragma once

#include "Core.h"
#include "Window.h"
#include "Raid/Events/AppEvent.h"
#include "LayerStack.h"

#include "Raid/ImGui/ImGuiLayer.h"

#include "Raid/Renderer/Shader.h"
#include "Raid/Renderer/Buffer.h"
#include "Raid/Renderer/VertexArray.h"

#include "Raid/Renderer/OrthographicCamera.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		~App();
		App(App&) = delete;
		App& operator=(const App&) = delete;

		inline static App& Get() { return *s_Instance; }

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApp();

}