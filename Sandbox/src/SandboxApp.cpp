#include <Shaddock.h>


class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}