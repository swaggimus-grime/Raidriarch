#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/AppEvent.h"
#include "LayerStack.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	App* CreateApp();

}