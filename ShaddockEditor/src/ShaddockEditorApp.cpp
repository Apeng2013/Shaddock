#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Shaddock {
	class ShaddockEditor : public Application
	{
	public:
		ShaddockEditor(const ApplicationSpecification& specification):
			Application(specification)
		{
			PushLayer(new EditorLayer());
		}
		~ShaddockEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "ShaddockEditor";
		spec.CommandLineArgs = args;
		return new ShaddockEditor(spec);
	}
}