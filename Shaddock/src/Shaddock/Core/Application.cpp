#include "sdpch.h"
#include "Shaddock/Core/Application.h"
#include "Shaddock/Core/Log.h"
#include "Shaddock/Core/Input.h"
#include "Shaddock/Renderer/Renderer.h"
#include "Shaddock/Renderer/RenderCommand.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Shaddock {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SD_PROFILE_FUNCTION();
		SD_CORE_ASSERT(!s_Instance, "Application alread exits!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(SD_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		
	}
	Application::~Application()
	{
		SD_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}
	void Application::Run()
	{
		SD_PROFILE_FUNCTION();
		while (m_Running)
		{
			SD_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;
			if (!m_Minimized)
			{
				SD_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(ts);
			}

			m_ImGuiLayer->Begin();
			{
				SD_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		SD_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		SD_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		SD_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SD_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SD_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto iter = m_LayerStack.rbegin(); iter != m_LayerStack.rend(); ++iter)
		{
			if (e.Handled)
				break;
			(*iter)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		SD_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}