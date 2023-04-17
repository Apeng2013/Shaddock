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

    static bool dockingEnabled = false;
    if (dockingEnabled)
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                if (ImGui::MenuItem("Exit")) Shaddock::Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();


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
    else
    {
        //static bool show_demo = true;
        //ImGui::ShowDemoWindow(&show_demo);

        ImGui::Begin("Image");
        uint32_t textureID = m_Texture->GetRendererID();
        ImGui::Image((void*)textureID, ImVec2(256.f, 256.f));
        ImGui::End();

        ImGui::Begin("Test");
        ImGui::Text("Test");
        ImGui::End();
    }
}

void Sandbox2D::OnEvent(Shaddock::Event& e)
{
	m_CameraController.OnEvent(e);
}
