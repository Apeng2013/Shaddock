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
		SD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Shaddock::Event& event) override
	{
		SD_INFO("{0}", event);
	}
};


class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}