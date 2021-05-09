#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/AppEvent.h"

namespace Raid {

	class RAID_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	App* CreateApp();

}