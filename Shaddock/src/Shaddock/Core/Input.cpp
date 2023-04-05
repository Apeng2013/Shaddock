#include "sdpch.h"
#include "Shaddock/Core/Input.h"

#ifdef SD_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Shaddock {
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef SD_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		SD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}