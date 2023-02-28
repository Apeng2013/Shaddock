#pragma once

#include "Core.h"
#include "Window.h"
#include "Shaddock/LayerStack.h"
#include "Shaddock/Events/Event.h"
#include "Shaddock/Events/ApplicationEvent.h"

#include "Shaddock/ImGui/ImGuiLayer.h"

#include "Shaddock/Renderer/Shader.h"
#include "Shaddock/Renderer/Buffer.h"
#include "Shaddock/Renderer/VertexArray.h"
#include "Shaddock/Renderer/OrthographicCamera.h"

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_BlueVertexArray;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}

