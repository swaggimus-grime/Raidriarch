#pragma once

#include "Raid/Core/Layer.h"

#include "Raid/Events/AppEvent.h"
#include "Raid/Events/MouseEvent.h"
#include "Raid/Events/KeyEvent.h"

namespace Raid {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; } 
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.f;
	};
}