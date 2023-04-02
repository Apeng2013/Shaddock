#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Shaddock::Texture2D::Create("assets/textures/letter_p.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Shaddock::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Shaddock::RenderCommand::Clear();

	Shaddock::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Shaddock::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Shaddock::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.2f, 0.2f, 0.8f, 1.0f });
	Shaddock::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
	Shaddock::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Shaddock::Event& e)
{
	m_CameraController.OnEvent(e);
}
