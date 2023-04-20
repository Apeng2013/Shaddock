#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Shaddock {
	class ShaddockEditor : public Application
	{
	public:
		ShaddockEditor():
			Application("Shaddock Editor")
		{
			PushLayer(new EditorLayer());
		}
		~ShaddockEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new ShaddockEditor();
	}
}