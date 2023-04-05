#pragma once
#include <Shaddock.h>

class ExampleLayer : public Shaddock::Layer
{
public:
	ExampleLayer();
	void OnUpdate(Shaddock::Timestep ts) override;

	void OnEvent(Shaddock::Event& event) override;

	void OnImGuiRender() override;
private:
	std::shared_ptr<Shaddock::Shader> m_Shader;
	std::shared_ptr<Shaddock::VertexArray> m_VertexArray;

	std::shared_ptr<Shaddock::Shader> m_FlatColorShader;
	std::shared_ptr<Shaddock::VertexArray> m_SquareVA;

	Shaddock::Ref<Shaddock::Texture2D> m_Texture;

	Shaddock::ShaderLibrary m_ShaderLibrary;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	Shaddock::OrthographicCameraController m_CameraController;

};

