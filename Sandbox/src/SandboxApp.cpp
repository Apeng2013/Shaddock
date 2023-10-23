#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Shaddock::Application
{
public:
	Sandbox(const Shaddock::ApplicationSpecification& specification)
		: Shaddock::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication(Shaddock::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../ShaddockEditor";
	spec.CommandLineArgs = args;
	return new Sandbox(spec);
}