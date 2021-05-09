#pragma once

#include "Core/Window.h"
#include <GLFW/glfw3.h>

namespace Raid {
	class GLFW_Window : public Window {
	public:
		GLFW_Window(const WindowProps& props);
		virtual ~GLFW_Window();

		void Update() override;

		inline unsigned int GetWidth() const override;
		inline unsigned int GetHeight() const override;

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		void Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		bool m_Closed = false;
		WindowData m_Data;
		
	};


}