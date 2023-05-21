#include "EditorLayer.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "Shaddock/Scene/SceneSerializer.h"
#include "Shaddock/Utils/PlatformUtils.h"
#include "Shaddock/Math/Math.h"
#include "ImGuizmo.h"
#include <chrono>

namespace Shaddock {
    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(1280.f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
    {
    }

    void EditorLayer::OnAttach()
    {
        SD_PROFILE_FUNCTION();
        m_Texture = Texture2D::Create("assets/textures/letter_p.png");

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        fbSpec.Attachments = { 
            FramebufferTextureFormat::RGBA8, 
            FramebufferTextureFormat::RED_INTEGER, 
            FramebufferTextureFormat::DEPTH24STENCIL8 
        };
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_ActiveScene = CreateRef<Scene>();

        m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

#if 0
        auto square = m_ActiveScene->CreateEntity("SquareEntity A");
        square.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        m_SquareEntity = square;

        auto squareB = m_ActiveScene->CreateEntity("SquareEntity B");
        squareB.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {
        public:
            virtual void OnCreate() override
            {

            }
            virtual void OnDestroy() override
            {

            }
            virtual void OnUpdate(Timestep ts) override
            {
                auto& translation = GetComponent<TransformComponent>().Translation;
                float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                    translation.x -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    translation.x += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    translation.y += speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    translation.y -= speed * ts;
            }
        };
        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
        m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OnDetach()
    {
        SD_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        SD_PROFILE_FUNCTION();

        const FramebufferSpecification& spec = m_Framebuffer->GetSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
        }

        if (m_ViewportFocused)
            m_CameraController.OnUpdate(ts);
        m_EditorCamera.OnUpdate(ts);

        Renderer2D::ResetStats();
        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();
        m_Framebuffer->ClearAttachment(1, -1);

        m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        my = m_ViewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;
        if (mouseX >= 0 && mouseY >= my && mouseX < (int)m_ViewportSize.x && mouseY < (int)m_ViewportSize.y)
        {
            int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
            m_HoverEntity = (pixelData == -1) ? Entity() : Entity((entt::entity)pixelData, m_ActiveScene.get());
        }

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        SD_PROFILE_FUNCTION();

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
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        style.WindowMinSize.x = minWinSizeX;
        
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Files"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                if (ImGui::MenuItem("New", "Ctrl+N"))
                    NewScene();
                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    OpenScene();
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    SaveSceneAs();
                if (ImGui::MenuItem("Exit")) Application::Get().Close();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        
        m_SceneHierarchyPanel.OnImGuiRender();
        
        // Render Statistic
        {
            ImGui::Begin("Statistic");
            std::string name = "None";
            if (m_HoverEntity)
                name = m_HoverEntity.GetComponent<TagComponent>().Tag;
            ImGui::Text("Hover Entity: %s", name.c_str());
            auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
            ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
            static bool open = true;
            ImGui::ShowDemoWindow(&open);
            ImGui::End();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport");
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

        // Gizmos
        {
            Entity& selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
            if (selectedEntity && m_GizmoType != -1)
            {
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();

                ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, 
                    m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y- m_ViewportBounds[0].y);
                
                const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
                glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

                auto& tc = selectedEntity.GetComponent<TransformComponent>();
                glm::mat4 transform = tc.GetTransform();

                bool snap = Input::IsKeyPressed(Key::LeftControl);
                float snapValue = m_GizmoType != ImGuizmo::OPERATION::ROTATE ? 0.5f : 45.0f;
                float snapValues[3] = { snapValue, snapValue, snapValue };

                ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), (ImGuizmo::OPERATION)m_GizmoType, 
                    ImGuizmo::LOCAL, glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);
                if (ImGuizmo::IsUsing())
                {
                    glm::vec3 translation, rotation, scale;
                    Math::DecomposeTransform(transform, translation, rotation, scale);
                    glm::vec3 deltaRotation = rotation - tc.Rotation;
                    tc.Translation = translation;
                    tc.Rotation += deltaRotation;
                    tc.Scale = scale;
                }

            }
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& e)
    {
        m_CameraController.OnEvent(e);
        m_EditorCamera.OnEvent(e);
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(SD_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }
    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
        bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
        switch (e.GetKeyCode())
        {
        case Key::N:
            if (control)
                NewScene();
            break;
        case Key::O:
            if (control)
                OpenScene();
            break;
        case Key::S:
            if (control && shift)
                SaveSceneAs();
            break;
        case Key::Q:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = -1;
            break;
        case Key::W:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case Key::E:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            break;
        case Key::R:
            if (!ImGuizmo::IsUsing())
                m_GizmoType = ImGuizmo::OPERATION::SCALE;
            break;
        }
        return false;
    }
    void EditorLayer::NewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }
    void EditorLayer::OpenScene()
    {
        std::optional<std::string> filepath = FileDialogs::OpenFile("Shaddock Scene (*.scene)\0*.scene\0");
        if (filepath)
        {
            m_ActiveScene = CreateRef<Scene>();
            m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_SceneHierarchyPanel.SetContext(m_ActiveScene);
            SceneSerializer serializer(m_ActiveScene);
            serializer.Deserialize(*filepath);
        }
    }
    void EditorLayer::SaveSceneAs()
    {
        std::optional<std::string> filepath = FileDialogs::SaveFile("Shaddock Scene (*.scene)\0*.scene\0");
        if (filepath)
        {
            SceneSerializer serializer(m_ActiveScene);
            serializer.Serialize(*filepath);
        }
    }
}

