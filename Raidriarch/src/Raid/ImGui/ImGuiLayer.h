#pragma once

#include "Raid/Core/Layer.h"

#include "Raid/Events/AppEvent.h"
#include "Raid/Events/MouseEvent.h"
#include "Raid/Events/KeyEvent.h"

namespace Raid {
	class RAID_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.f;
	};
}