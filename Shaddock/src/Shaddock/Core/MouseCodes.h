#pragma once

#include <sstream>

namespace Shaddock
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

#define SD_MOUSE_BUTTON_0      ::Shaddock::Mouse::Button0
#define SD_MOUSE_BUTTON_1      ::Shaddock::Mouse::Button1
#define SD_MOUSE_BUTTON_2      ::Shaddock::Mouse::Button2
#define SD_MOUSE_BUTTON_3      ::Shaddock::Mouse::Button3
#define SD_MOUSE_BUTTON_4      ::Shaddock::Mouse::Button4
#define SD_MOUSE_BUTTON_5      ::Shaddock::Mouse::Button5
#define SD_MOUSE_BUTTON_6      ::Shaddock::Mouse::Button6
#define SD_MOUSE_BUTTON_7      ::Shaddock::Mouse::Button7
#define SD_MOUSE_BUTTON_LAST   ::Shaddock::Mouse::ButtonLast
#define SD_MOUSE_BUTTON_LEFT   ::Shaddock::Mouse::ButtonLeft
#define SD_MOUSE_BUTTON_RIGHT  ::Shaddock::Mouse::ButtonRight
#define SD_MOUSE_BUTTON_MIDDLE ::Shaddock::Mouse::ButtonMiddle