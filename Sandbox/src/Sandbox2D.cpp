#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	SD_PROFILE_FUNCTION();
	m_Texture = Shaddock::Texture2D::Create("assets/textures/letter_p.png");
}

void Sandbox2D::OnDetach()
{
	SD_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Shaddock::Timestep ts)
{
	SD_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(ts);
	{
		SD_PROFILE_SCOPE("Sandbox2D::Renderer");
		Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Shaddock::RenderCommand::Clear();

		Shaddock::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Shaddock::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Shaddock::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.2f, 0.2f, 0.8f, 1.0f });
		Shaddock::Renderer2D::DrawRotatedQuad({ 1.0f, 1.0f }, { 1.0f, 1.0f }, glm::radians(45.0f), { 0.2f, 0.8f, 0.2f, 1.0f });
		Shaddock::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 1.0f }, m_Texture);
		Shaddock::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SD_PROFILE_FUNCTION();
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Shaddock::Event& e)
{
	m_CameraController.OnEvent(e);
}
