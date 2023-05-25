#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Shaddock {
	class ShaddockEditor : public Application
	{
	public:
		ShaddockEditor(ApplicationCommandLineArgs args):
			Application("Shaddock Editor", args)
		{
			PushLayer(new EditorLayer());
		}
		~ShaddockEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new ShaddockEditor(args);
	}
}