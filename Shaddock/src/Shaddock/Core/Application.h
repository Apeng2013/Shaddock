#pragma once

#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/Window.h"
#include "Shaddock/Core/LayerStack.h"
#include "Shaddock/Core/Timestep.h"

#include "Shaddock/Events/Event.h"
#include "Shaddock/Events/ApplicationEvent.h"

#include "Shaddock/ImGui/ImGuiLayer.h"

#include "Shaddock/Renderer/Shader.h"
#include "Shaddock/Renderer/Buffer.h"
#include "Shaddock/Renderer/VertexArray.h"
#include "Shaddock/Renderer/OrthographicCamera.h"

int main(int argc, char** argv);

namespace Shaddock {
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			SD_CORE_ASSERT(index < Count, "");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Shaddock Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
		const ApplicationSpecification GetSpecification() const { return m_Specification; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//To be defined in Client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

