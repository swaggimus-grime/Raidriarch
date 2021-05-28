#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Renderer/OrthographicCamera.h"

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
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static App* s_Instance;
	};

	// To be defined in CLIENT
	App* CreateApp();

}