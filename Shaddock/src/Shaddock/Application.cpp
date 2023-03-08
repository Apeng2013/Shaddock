#include "sdpch.h"
#include "Application.h"

#include "Shaddock/Log.h"
#include <glad/glad.h>
#include "Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "GLFW/glfw3.h"

namespace Shaddock {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SD_CORE_ASSERT(!s_Instance, "Application alread exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Renderer::Init();
		
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{
		while (m_Running)
		{

			float time = (float)glfwGetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}