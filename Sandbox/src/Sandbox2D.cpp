#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.0f), m_SquareColor({0.2f, 0.3f, 0.8f, 1.0f})
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
	Shaddock::Renderer2D::ResetStats();
	{
		SD_PROFILE_SCOPE("Sandbox2D::Renderer");
		Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Shaddock::RenderCommand::Clear();
		Shaddock::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Shaddock::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Shaddock::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Shaddock::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture); //°ëÍ¸Ã÷ ×¢ÒâäÖÈ¾Ë³Ðò
		Shaddock::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, 0.2f}, { 1.0f, 1.0f }, 45.0f, { 0.2f, 0.8f, 0.2f, 1.0f });
		Shaddock::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f, 0.2f}, { 1.0f, 1.0f }, 45.0f, { 0.2f, 0.8f, 0.2f, 1.0f });
		Shaddock::Renderer2D::EndScene();

		Shaddock::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 0.5f) / 10.0f, 0.4f, (y + 0.5f) / 10.0f, 0.7f}; //°ëÍ¸Ã÷ ×¢ÒâäÖÈ¾Ë³Ðò
				Shaddock::Renderer2D::DrawQuad({ x, y }, { 0.45, 0.45 }, color);
			}
		}
		Shaddock::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	SD_PROFILE_FUNCTION();
	ImGui::Begin("Setting");
	auto stats = Shaddock::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Shaddock::Event& e)
{
	m_CameraController.OnEvent(e);
}
