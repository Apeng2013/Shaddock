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
		if (Shaddock::Input::IsKeyPressed(SD_KEY_TAB))
		{
			SD_TRACE("Tab key is pressed(poll)!");
		}
	}

	void OnEvent(Shaddock::Event& event) override
	{
		if (event.GetEventType() == Shaddock::EventType::KeyPressed)
		{
			Shaddock::KeyPressedEvent& e = (Shaddock::KeyPressedEvent&)event;
			if (e.GetKeyCode() == SD_KEY_TAB)
				SD_TRACE("Tab key is pressed(event)!");
			SD_TRACE("{0}", (char)e.GetKeyCode());
		}
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