#pragma once

namespace Raid
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define RAID_KEY_SPACE           ::Raid::Key::Space
#define RAID_KEY_APOSTROPHE      ::Raid::Key::Apostrophe    /* ' */
#define RAID_KEY_COMMA           ::Raid::Key::Comma         /* , */
#define RAID_KEY_MINUS           ::Raid::Key::Minus         /* - */
#define RAID_KEY_PERIOD          ::Raid::Key::Period        /* . */
#define RAID_KEY_SLASH           ::Raid::Key::Slash         /* / */
#define RAID_KEY_0               ::Raid::Key::D0
#define RAID_KEY_1               ::Raid::Key::D1
#define RAID_KEY_2               ::Raid::Key::D2
#define RAID_KEY_3               ::Raid::Key::D3
#define RAID_KEY_4               ::Raid::Key::D4
#define RAID_KEY_5               ::Raid::Key::D5
#define RAID_KEY_6               ::Raid::Key::D6
#define RAID_KEY_7               ::Raid::Key::D7
#define RAID_KEY_8               ::Raid::Key::D8
#define RAID_KEY_9               ::Raid::Key::D9
#define RAID_KEY_SEMICOLON       ::Raid::Key::Semicolon     /* ; */
#define RAID_KEY_EQUAL           ::Raid::Key::Equal         /* = */
#define RAID_KEY_A               ::Raid::Key::A
#define RAID_KEY_B               ::Raid::Key::B
#define RAID_KEY_C               ::Raid::Key::C
#define RAID_KEY_D               ::Raid::Key::D
#define RAID_KEY_E               ::Raid::Key::E
#define RAID_KEY_F               ::Raid::Key::F
#define RAID_KEY_G               ::Raid::Key::G
#define RAID_KEY_H               ::Raid::Key::H
#define RAID_KEY_I               ::Raid::Key::I
#define RAID_KEY_J               ::Raid::Key::J
#define RAID_KEY_K               ::Raid::Key::K
#define RAID_KEY_L               ::Raid::Key::L
#define RAID_KEY_M               ::Raid::Key::M
#define RAID_KEY_N               ::Raid::Key::N
#define RAID_KEY_O               ::Raid::Key::O
#define RAID_KEY_P               ::Raid::Key::P
#define RAID_KEY_Q               ::Raid::Key::Q
#define RAID_KEY_R               ::Raid::Key::R
#define RAID_KEY_S               ::Raid::Key::S
#define RAID_KEY_T               ::Raid::Key::T
#define RAID_KEY_U               ::Raid::Key::U
#define RAID_KEY_V               ::Raid::Key::V
#define RAID_KEY_W               ::Raid::Key::W
#define RAID_KEY_X               ::Raid::Key::X
#define RAID_KEY_Y               ::Raid::Key::Y
#define RAID_KEY_Z               ::Raid::Key::Z
#define RAID_KEY_LEFT_BRACKET    ::Raid::Key::LeftBracket   /* [ */
#define RAID_KEY_BACKSLASH       ::Raid::Key::Backslash     /* \ */
#define RAID_KEY_RIGHT_BRACKET   ::Raid::Key::RightBracket  /* ] */
#define RAID_KEY_GRAVE_ACCENT    ::Raid::Key::GraveAccent   /* ` */
#define RAID_KEY_WORLD_1         ::Raid::Key::World1        /* non-US #1 */
#define RAID_KEY_WORLD_2         ::Raid::Key::World2        /* non-US #2 */

/* Function keys */
#define RAID_KEY_ESCAPE          ::Raid::Key::Escape
#define RAID_KEY_ENTER           ::Raid::Key::Enter
#define RAID_KEY_TAB             ::Raid::Key::Tab
#define RAID_KEY_BACKSPACE       ::Raid::Key::Backspace
#define RAID_KEY_INSERT          ::Raid::Key::Insert
#define RAID_KEY_DELETE          ::Raid::Key::Delete
#define RAID_KEY_RIGHT           ::Raid::Key::Right
#define RAID_KEY_LEFT            ::Raid::Key::Left
#define RAID_KEY_DOWN            ::Raid::Key::Down
#define RAID_KEY_UP              ::Raid::Key::Up
#define RAID_KEY_PAGE_UP         ::Raid::Key::PageUp
#define RAID_KEY_PAGE_DOWN       ::Raid::Key::PageDown
#define RAID_KEY_HOME            ::Raid::Key::Home
#define RAID_KEY_END             ::Raid::Key::End
#define RAID_KEY_CAPS_LOCK       ::Raid::Key::CapsLock
#define RAID_KEY_SCROLL_LOCK     ::Raid::Key::ScrollLock
#define RAID_KEY_NUM_LOCK        ::Raid::Key::NumLock
#define RAID_KEY_PRINT_SCREEN    ::Raid::Key::PrintScreen
#define RAID_KEY_PAUSE           ::Raid::Key::Pause
#define RAID_KEY_F1              ::Raid::Key::F1
#define RAID_KEY_F2              ::Raid::Key::F2
#define RAID_KEY_F3              ::Raid::Key::F3
#define RAID_KEY_F4              ::Raid::Key::F4
#define RAID_KEY_F5              ::Raid::Key::F5
#define RAID_KEY_F6              ::Raid::Key::F6
#define RAID_KEY_F7              ::Raid::Key::F7
#define RAID_KEY_F8              ::Raid::Key::F8
#define RAID_KEY_F9              ::Raid::Key::F9
#define RAID_KEY_F10             ::Raid::Key::F10
#define RAID_KEY_F11             ::Raid::Key::F11
#define RAID_KEY_F12             ::Raid::Key::F12
#define RAID_KEY_F13             ::Raid::Key::F13
#define RAID_KEY_F14             ::Raid::Key::F14
#define RAID_KEY_F15             ::Raid::Key::F15
#define RAID_KEY_F16             ::Raid::Key::F16
#define RAID_KEY_F17             ::Raid::Key::F17
#define RAID_KEY_F18             ::Raid::Key::F18
#define RAID_KEY_F19             ::Raid::Key::F19
#define RAID_KEY_F20             ::Raid::Key::F20
#define RAID_KEY_F21             ::Raid::Key::F21
#define RAID_KEY_F22             ::Raid::Key::F22
#define RAID_KEY_F23             ::Raid::Key::F23
#define RAID_KEY_F24             ::Raid::Key::F24
#define RAID_KEY_F25             ::Raid::Key::F25

/* Keypad */
#define RAID_KEY_KP_0            ::Raid::Key::KP0
#define RAID_KEY_KP_1            ::Raid::Key::KP1
#define RAID_KEY_KP_2            ::Raid::Key::KP2
#define RAID_KEY_KP_3            ::Raid::Key::KP3
#define RAID_KEY_KP_4            ::Raid::Key::KP4
#define RAID_KEY_KP_5            ::Raid::Key::KP5
#define RAID_KEY_KP_6            ::Raid::Key::KP6
#define RAID_KEY_KP_7            ::Raid::Key::KP7
#define RAID_KEY_KP_8            ::Raid::Key::KP8
#define RAID_KEY_KP_9            ::Raid::Key::KP9
#define RAID_KEY_KP_DECIMAL      ::Raid::Key::KPDecimal
#define RAID_KEY_KP_DIVIDE       ::Raid::Key::KPDivide
#define RAID_KEY_KP_MULTIPLY     ::Raid::Key::KPMultiply
#define RAID_KEY_KP_SUBTRACT     ::Raid::Key::KPSubtract
#define RAID_KEY_KP_ADD          ::Raid::Key::KPAdd
#define RAID_KEY_KP_ENTER        ::Raid::Key::KPEnter
#define RAID_KEY_KP_EQUAL        ::Raid::Key::KPEqual

#define RAID_KEY_LEFT_SHIFT      ::Raid::Key::LeftShift
#define RAID_KEY_LEFT_CONTROL    ::Raid::Key::LeftControl
#define RAID_KEY_LEFT_ALT        ::Raid::Key::LeftAlt
#define RAID_KEY_LEFT_SUPER      ::Raid::Key::LeftSuper
#define RAID_KEY_RIGHT_SHIFT     ::Raid::Key::RightShift
#define RAID_KEY_RIGHT_CONTROL   ::Raid::Key::RightControl
#define RAID_KEY_RIGHT_ALT       ::Raid::Key::RightAlt
#define RAID_KEY_RIGHT_SUPER     ::Raid::Key::RightSuper
#define RAID_KEY_MENU            ::Raid::Key::Menu