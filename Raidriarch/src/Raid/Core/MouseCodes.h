#pragma once

namespace Raid
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define RAID_MOUSE_BUTTON_0      ::Raid::Mouse::Button0
#define RAID_MOUSE_BUTTON_1      ::Raid::Mouse::Button1
#define RAID_MOUSE_BUTTON_2      ::Raid::Mouse::Button2
#define RAID_MOUSE_BUTTON_3      ::Raid::Mouse::Button3
#define RAID_MOUSE_BUTTON_4      ::Raid::Mouse::Button4
#define RAID_MOUSE_BUTTON_5      ::Raid::Mouse::Button5
#define RAID_MOUSE_BUTTON_6      ::Raid::Mouse::Button6
#define RAID_MOUSE_BUTTON_7      ::Raid::Mouse::Button7
#define RAID_MOUSE_BUTTON_LAST   ::Raid::Mouse::ButtonLast
#define RAID_MOUSE_BUTTON_LEFT   ::Raid::Mouse::ButtonLeft
#define RAID_MOUSE_BUTTON_RIGHT  ::Raid::Mouse::ButtonRight
#define RAID_MOUSE_BUTTON_MIDDLE ::Raid::Mouse::ButtonMiddle