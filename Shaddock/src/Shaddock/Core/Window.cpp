#include "sdpch.h"
#include "Shaddock/Core/Window.h"

#ifdef SD_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Shaddock {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef SD_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		SD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}