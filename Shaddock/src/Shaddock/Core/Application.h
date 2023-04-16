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

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
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
	Application* CreateApplication();
}

