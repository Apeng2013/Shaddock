#pragma once
#include "Shaddock.h"

class Sandbox2D : public Shaddock::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Shaddock::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Shaddock::Event& e) override;

private:
	Shaddock::OrthographicCameraController m_CameraController;
	Shaddock::Ref<Shaddock::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
