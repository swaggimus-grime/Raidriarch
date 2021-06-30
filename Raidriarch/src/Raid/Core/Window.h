#pragma once

#include "raidpch.h"
#include "Raid/Events/Event.h"
#include "Raid/Core/Core.h"

namespace Raid {

	//Contains the properties for a window
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "RAIDRIARCH", 
			unsigned int width = 1280, unsigned height = 720) 
		: Title(title), Width(width), Height(height) 
		{
		}
	};

	//Interface that lists functionality for a window 
	class RAID_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;


		virtual inline unsigned int GetWidth() const = 0;
		virtual inline unsigned int GetHeight() const = 0;

		//Window attribs
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}