#include <Shaddock.h>
#include <Shaddock/Core/EntryPoint.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include "Sandbox2D.h"

class ExampleLayer : public Shaddock::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.f)
	{
		m_VertexArray = Shaddock::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Shaddock::Ref<Shaddock::VertexBuffer> vertexBuffer = Shaddock::VertexBuffer::Create(vertices, sizeof(vertices));
		Shaddock::BufferLayout layout = {
			{Shaddock::ShaderDataType::Float3, "a_Position"},
			{Shaddock::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		Shaddock::Ref<Shaddock::IndexBuffer> indexBuffer = Shaddock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Shaddock::Shader::Create("VertexColorShader", vertexSrc, fragmentSrc);

		// flat color shader
		m_SquareVA = Shaddock::VertexArray::Create();

		float square_vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		Shaddock::Ref<Shaddock::VertexBuffer> squareVertexBuffer = Shaddock::VertexBuffer::Create(square_vertices, sizeof(square_vertices));
		Shaddock::BufferLayout square_layout = {
			{Shaddock::ShaderDataType::Float3, "a_Position"},
			{Shaddock::ShaderDataType::Float2, "a_TexCoord"},
		};
		squareVertexBuffer->SetLayout(square_layout);

		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		unsigned int square_indices[6] = { 0, 1, 2 , 3, 2, 1 };

		Shaddock::Ref<Shaddock::IndexBuffer> squareIndexBuffer = Shaddock::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));

		m_SquareVA->SetIndexBuffer(squareIndexBuffer);

		std::string flatColorVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Shaddock::Shader::Create("FlatColorShader", flatColorVertexSrc, flatColorFragmentSrc);

		
		m_Texture = Shaddock::Texture2D::Create("assets/textures/letter_p.png");
		m_Texture->Bind();
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		textureShader->SetInt("u_Texture", 0);
	}
	void OnUpdate(Shaddock::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
		
		Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Shaddock::RenderCommand::Clear();

		Shaddock::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Shaddock::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		m_Texture->Bind();
		auto textureShader = m_ShaderLibrary.Get("Texture");
		Shaddock::Renderer::Submit(textureShader, m_SquareVA);
		//Shaddock::Renderer::Submit(m_Shader, m_VertexArray);

		Shaddock::Renderer::EndScene();
	}

	void OnEvent(Shaddock::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

	void OnImGuiRender()
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
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


class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}