#pragma once

#include "Raid/Core/Core.h"
#include "Raid/Core/KeyCodes.h"
#include "Raid/Core/MouseCodes.h"

namespace Raid {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}