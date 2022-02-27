#include <Shaddock.h>

class ExampleLayer : public Shaddock::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}
	void OnUpdate() override
	{
	}

	void OnEvent(Shaddock::Event& event) override
	{
	}
};


class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Shaddock::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}