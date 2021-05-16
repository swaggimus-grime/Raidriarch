#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "LayerStack.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		virtual ~App();

		inline static App& Get() { return *m_Instance; }

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static App* m_Instance;
	};

	// To be defined in CLIENT
	App* CreateApp();

}