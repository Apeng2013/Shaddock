#pragma once

#include "Core.h"
#include "Window.h"
#include "Shaddock/Core/LayerStack.h"
#include "Shaddock/Events/Event.h"
#include "Shaddock/Events/ApplicationEvent.h"

#include "Shaddock/ImGui/ImGuiLayer.h"

#include "Shaddock/Renderer/Shader.h"
#include "Shaddock/Renderer/Buffer.h"
#include "Shaddock/Renderer/VertexArray.h"
#include "Shaddock/Renderer/OrthographicCamera.h"

#include "Shaddock/Core/Timestep.h"

namespace Shaddock {

	class SHADDOCK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
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
	};

	//To be defined in Client
	Application* CreateApplication();
}
