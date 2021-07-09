#pragma once

#include "raidpch.h"
#include "Raid/Events/Event.h"
#include "Raid/Core/Core.h"

namespace Raid {

	//Contains the properties for a window
	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "RAIDRIARCH", 
			uint32_t width = 1280, uint32_t height = 720)
		: Title(title), Width(width), Height(height) 
		{
		}
	};

	//Interface that lists functionality for a window 
	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;


		virtual inline uint32_t GetWidth() const = 0;
		virtual inline uint32_t GetHeight() const = 0;

		//Window attribs
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}