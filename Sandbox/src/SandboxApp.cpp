#include <Shaddock.h>

#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public Shaddock::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Shaddock::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Shaddock::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Shaddock::VertexBuffer::Create(vertices, sizeof(vertices)));
		Shaddock::BufferLayout layout = {
			{Shaddock::ShaderDataType::Float3, "a_Position"},
			{Shaddock::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		std::shared_ptr<Shaddock::IndexBuffer> indexBuffer;
		indexBuffer.reset(Shaddock::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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

		m_Shader.reset(new Shaddock::Shader(vertexSrc, fragmentSrc));

		// blue shader
		m_BlueVertexArray.reset(Shaddock::VertexArray::Create());

		float blue_vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 -0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<Shaddock::VertexBuffer> blueVertexBuffer;
		blueVertexBuffer.reset(Shaddock::VertexBuffer::Create(blue_vertices, sizeof(blue_vertices)));
		Shaddock::BufferLayout blue_layout = {
			{Shaddock::ShaderDataType::Float3, "a_Position"},
		};
		blueVertexBuffer->SetLayout(blue_layout);

		m_BlueVertexArray->AddVertexBuffer(blueVertexBuffer);

		unsigned int blue_indices[6] = { 0, 1, 2 , 3, 2, 1 };

		std::shared_ptr<Shaddock::IndexBuffer> blueIndexBuffer;
		blueIndexBuffer.reset(Shaddock::IndexBuffer::Create(blue_indices, sizeof(blue_indices) / sizeof(uint32_t)));

		m_BlueVertexArray->SetIndexBuffer(blueIndexBuffer);

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Shaddock::Shader(blueVertexSrc, blueFragmentSrc));
	}
	void OnUpdate(Shaddock::Timestep ts) override
	{
		if (Shaddock::Input::IsKeyPressed(SD_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (Shaddock::Input::IsKeyPressed(SD_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (Shaddock::Input::IsKeyPressed(SD_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		if (Shaddock::Input::IsKeyPressed(SD_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Shaddock::Input::IsKeyPressed(SD_KEY_A))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		if (Shaddock::Input::IsKeyPressed(SD_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		Shaddock::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Shaddock::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Shaddock::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Shaddock::Renderer::Submit(m_BlueShader, m_BlueVertexArray, transform);
			}
		}
		Shaddock::Renderer::Submit(m_Shader, m_VertexArray);

		Shaddock::Renderer::EndScene();
	}

	void OnEvent(Shaddock::Event& event) override
	{

	}
private:
	std::shared_ptr<Shaddock::Shader> m_Shader;
	std::shared_ptr<Shaddock::VertexArray> m_VertexArray;

	std::shared_ptr<Shaddock::Shader> m_BlueShader;
	std::shared_ptr<Shaddock::VertexArray> m_BlueVertexArray;

	Shaddock::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotateSpeed = 180.0f;

};


class Sandbox : public Shaddock::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Shaddock::Application* Shaddock::CreateApplication()
{
	return new Sandbox();
}