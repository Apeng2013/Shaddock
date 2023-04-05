#pragma once
#include "Shaddock/Core/Core.h"

#ifdef SD_PLATFORM_WINDOWS

extern Shaddock::Application* Shaddock::CreateApplication();

int main(int argc, char** argv)
{
	Shaddock::Log().Init();

	SD_PROFILE_BEGIN_SESSION("Startup", "ShaddockProfile-Startup.json");
	Shaddock::Application* app = Shaddock::CreateApplication();
	SD_PROFILE_END_SESSION();

	SD_PROFILE_BEGIN_SESSION("Runtime", "ShaddockProfile-Runtime.json");
	app->Run();
	SD_PROFILE_END_SESSION();

	SD_PROFILE_BEGIN_SESSION("Shutdown", "ShaddockProfile-Shutdown.json");
	delete app;
	SD_PROFILE_END_SESSION();

	return 0;
}

#endif