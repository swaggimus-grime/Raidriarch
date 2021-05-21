#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		virtual ~App();

		inline static App& Get() { return *s_Instance; }

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApp();

}