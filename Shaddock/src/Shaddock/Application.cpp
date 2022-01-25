#include "sdpch.h"
#include "Application.h"

#include "Shaddock/Events/ApplicationEvent.h"
#include "Shaddock/Log.h"


namespace Shaddock {

	Application::Application()
	{

	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			SD_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			SD_TRACE(e);
		}
		while (true);
	}
}