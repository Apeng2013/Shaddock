#pragma once

#include <sstream>

namespace Shaddock
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum KeyCode
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
		};
	};
}

#define SD_KEY_SPACE           ::Shaddock::Key::Space
#define SD_KEY_APOSTROPHE      ::Shaddock::Key::Apostrophe    /* ' */
#define SD_KEY_COMMA           ::Shaddock::Key::Comma         /* , */
#define SD_KEY_MINUS           ::Shaddock::Key::Minus         /* - */
#define SD_KEY_PERIOD          ::Shaddock::Key::Period        /* . */
#define SD_KEY_SLASH           ::Shaddock::Key::Slash         /* / */
#define SD_KEY_0               ::Shaddock::Key::D0
#define SD_KEY_1               ::Shaddock::Key::D1
#define SD_KEY_2               ::Shaddock::Key::D2
#define SD_KEY_3               ::Shaddock::Key::D3
#define SD_KEY_4               ::Shaddock::Key::D4
#define SD_KEY_5               ::Shaddock::Key::D5
#define SD_KEY_6               ::Shaddock::Key::D6
#define SD_KEY_7               ::Shaddock::Key::D7
#define SD_KEY_8               ::Shaddock::Key::D8
#define SD_KEY_9               ::Shaddock::Key::D9
#define SD_KEY_SEMICOLON       ::Shaddock::Key::Semicolon     /* ; */
#define SD_KEY_EQUAL           ::Shaddock::Key::Equal         /* = */
#define SD_KEY_A               ::Shaddock::Key::A
#define SD_KEY_B               ::Shaddock::Key::B
#define SD_KEY_C               ::Shaddock::Key::C
#define SD_KEY_D               ::Shaddock::Key::D
#define SD_KEY_E               ::Shaddock::Key::E
#define SD_KEY_F               ::Shaddock::Key::F
#define SD_KEY_G               ::Shaddock::Key::G
#define SD_KEY_H               ::Shaddock::Key::H
#define SD_KEY_I               ::Shaddock::Key::I
#define SD_KEY_J               ::Shaddock::Key::J
#define SD_KEY_K               ::Shaddock::Key::K
#define SD_KEY_L               ::Shaddock::Key::L
#define SD_KEY_M               ::Shaddock::Key::M
#define SD_KEY_N               ::Shaddock::Key::N
#define SD_KEY_O               ::Shaddock::Key::O
#define SD_KEY_P               ::Shaddock::Key::P
#define SD_KEY_Q               ::Shaddock::Key::Q
#define SD_KEY_R               ::Shaddock::Key::R
#define SD_KEY_S               ::Shaddock::Key::S
#define SD_KEY_T               ::Shaddock::Key::T
#define SD_KEY_U               ::Shaddock::Key::U
#define SD_KEY_V               ::Shaddock::Key::V
#define SD_KEY_W               ::Shaddock::Key::W
#define SD_KEY_X               ::Shaddock::Key::X
#define SD_KEY_Y               ::Shaddock::Key::Y
#define SD_KEY_Z               ::Shaddock::Key::Z
#define SD_KEY_LEFT_BRACKET    ::Shaddock::Key::LeftBracket   /* [ */
#define SD_KEY_BACKSLASH       ::Shaddock::Key::Backslash     /* \ */
#define SD_KEY_RIGHT_BRACKET   ::Shaddock::Key::RightBracket  /* ] */
#define SD_KEY_GRAVE_ACCENT    ::Shaddock::Key::GraveAccent   /* ` */
#define SD_KEY_WORLD_1         ::Shaddock::Key::World1        /* non-US #1 */
#define SD_KEY_WORLD_2         ::Shaddock::Key::World2        /* non-US #2 */
#define SD_KEY_ESCAPE          ::Shaddock::Key::Escape
#define SD_KEY_ENTER           ::Shaddock::Key::Enter
#define SD_KEY_TAB             ::Shaddock::Key::Tab
#define SD_KEY_BACKSPACE       ::Shaddock::Key::Backspace
#define SD_KEY_INSERT          ::Shaddock::Key::Insert
#define SD_KEY_DELETE          ::Shaddock::Key::Delete
#define SD_KEY_RIGHT           ::Shaddock::Key::Right
#define SD_KEY_LEFT            ::Shaddock::Key::Left
#define SD_KEY_DOWN            ::Shaddock::Key::Down
#define SD_KEY_UP              ::Shaddock::Key::Up
#define SD_KEY_PAGE_UP         ::Shaddock::Key::PageUp
#define SD_KEY_PAGE_DOWN       ::Shaddock::Key::PageDown
#define SD_KEY_HOME            ::Shaddock::Key::Home
#define SD_KEY_END             ::Shaddock::Key::End
#define SD_KEY_CAPS_LOCK       ::Shaddock::Key::CapsLock
#define SD_KEY_SCROLL_LOCK     ::Shaddock::Key::ScrollLock
#define SD_KEY_NUM_LOCK        ::Shaddock::Key::NumLock
#define SD_KEY_PRINT_SCREEN    ::Shaddock::Key::PrintScreen
#define SD_KEY_PAUSE           ::Shaddock::Key::Pause
#define SD_KEY_F1              ::Shaddock::Key::F1
#define SD_KEY_F2              ::Shaddock::Key::F2
#define SD_KEY_F3              ::Shaddock::Key::F3
#define SD_KEY_F4              ::Shaddock::Key::F4
#define SD_KEY_F5              ::Shaddock::Key::F5
#define SD_KEY_F6              ::Shaddock::Key::F6
#define SD_KEY_F7              ::Shaddock::Key::F7
#define SD_KEY_F8              ::Shaddock::Key::F8
#define SD_KEY_F9              ::Shaddock::Key::F9
#define SD_KEY_F10             ::Shaddock::Key::F10
#define SD_KEY_F11             ::Shaddock::Key::F11
#define SD_KEY_F12             ::Shaddock::Key::F12
#define SD_KEY_F13             ::Shaddock::Key::F13
#define SD_KEY_F14             ::Shaddock::Key::F14
#define SD_KEY_F15             ::Shaddock::Key::F15
#define SD_KEY_F16             ::Shaddock::Key::F16
#define SD_KEY_F17             ::Shaddock::Key::F17
#define SD_KEY_F18             ::Shaddock::Key::F18
#define SD_KEY_F19             ::Shaddock::Key::F19
#define SD_KEY_F20             ::Shaddock::Key::F20
#define SD_KEY_F21             ::Shaddock::Key::F21
#define SD_KEY_F22             ::Shaddock::Key::F22
#define SD_KEY_F23             ::Shaddock::Key::F23
#define SD_KEY_F24             ::Shaddock::Key::F24
#define SD_KEY_F25             ::Shaddock::Key::F25

/* Keypad */
#define SD_KEY_KP_0            ::Shaddock::Key::KP0
#define SD_KEY_KP_1            ::Shaddock::Key::KP1
#define SD_KEY_KP_2            ::Shaddock::Key::KP2
#define SD_KEY_KP_3            ::Shaddock::Key::KP3
#define SD_KEY_KP_4            ::Shaddock::Key::KP4
#define SD_KEY_KP_5            ::Shaddock::Key::KP5
#define SD_KEY_KP_6            ::Shaddock::Key::KP6
#define SD_KEY_KP_7            ::Shaddock::Key::KP7
#define SD_KEY_KP_8            ::Shaddock::Key::KP8
#define SD_KEY_KP_9            ::Shaddock::Key::KP9
#define SD_KEY_KP_DECIMAL      ::Shaddock::Key::KPDecimal
#define SD_KEY_KP_DIVIDE       ::Shaddock::Key::KPDivide
#define SD_KEY_KP_MULTIPLY     ::Shaddock::Key::KPMultiply
#define SD_KEY_KP_SUBTRACT     ::Shaddock::Key::KPSubtract
#define SD_KEY_KP_ADD          ::Shaddock::Key::KPAdd
#define SD_KEY_KP_ENTER        ::Shaddock::Key::KPEnter
#define SD_KEY_KP_EQUAL        ::Shaddock::Key::KPEqual

#define SD_KEY_LEFT_SHIFT      ::Shaddock::Key::LeftShift
#define SD_KEY_LEFT_CONTROL    ::Shaddock::Key::LeftControl
#define SD_KEY_LEFT_ALT        ::Shaddock::Key::LeftAlt
#define SD_KEY_LEFT_SUPER      ::Shaddock::Key::LeftSuper
#define SD_KEY_RIGHT_SHIFT     ::Shaddock::Key::RightShift
#define SD_KEY_RIGHT_CONTROL   ::Shaddock::Key::RightControl
#define SD_KEY_RIGHT_ALT       ::Shaddock::Key::RightAlt
#define SD_KEY_RIGHT_SUPER     ::Shaddock::Key::RightSuper
#define SD_KEY_MENU            ::Shaddock::Key::Menu
