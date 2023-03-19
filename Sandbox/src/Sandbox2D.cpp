#include "sdpch.h"
#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Shaddock::VertexArray::Create();

	float vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	std::shared_ptr<Shaddock::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Shaddock::VertexBuffer::Create(vertices, sizeof(vertices)));
	Shaddock::BufferLayout layout = {
		{Shaddock::ShaderDataType::Float3, "a_Position"},
	};
	vertexBuffer->SetLayout(layout);
	m_SquareVA->AddVertexBuffer(vertexBuffer);

	unsigned int indices[6] = { 0, 1, 2, 2, 3, 0};
	std::shared_ptr<Shaddock::IndexBuffer> indexBuffer;
	indexBuffer.reset(Shaddock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(indexBuffer);

	m_FlatColorShader = Shaddock::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Shaddock::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Shaddock::RenderCommand::Clear();

	Shaddock::Renderer::BeginScene(m_CameraController.GetCamera());

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Shaddock::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	Shaddock::Renderer::Submit(m_FlatColorShader, m_SquareVA);

	Shaddock::Renderer::EndScene();
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
