#pragma once
#include "Shaddock.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Shaddock/Renderer/EditorCamera.h"

namespace Shaddock {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		OrthographicCameraController m_CameraController;
		Ref<Shaddock::Texture2D> m_Texture;
		Ref<Shaddock::Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		SceneHierarchyPanel m_SceneHierarchyPanel;

		int m_GizmoType = -1;

		EditorCamera m_EditorCamera;

		glm::vec2 m_ViewportBounds[2];
		Entity m_HoverEntity;

	};
}
