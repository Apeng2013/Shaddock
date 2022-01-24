#pragma once

#ifdef SD_PLATFORM_WINDOWS

extern Shaddock::Application* Shaddock::CreateApplication();

int main(int argc, char** argv)
{
	Shaddock::Log().Init();
	SD_INFO("Hello, var={0}", 123);

	Shaddock::Application* app = Shaddock::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif