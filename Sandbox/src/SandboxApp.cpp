#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}