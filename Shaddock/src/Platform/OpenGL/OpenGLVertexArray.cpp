#include "sdpch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Shaddock {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Shaddock::ShaderDataType::Float:    return GL_FLOAT;
		case Shaddock::ShaderDataType::Float2:   return GL_FLOAT;
		case Shaddock::ShaderDataType::Float3:   return GL_FLOAT;
		case Shaddock::ShaderDataType::Float4:   return GL_FLOAT;
		case Shaddock::ShaderDataType::Mat3:     return GL_FLOAT;
		case Shaddock::ShaderDataType::Mat4:     return GL_FLOAT;
		case Shaddock::ShaderDataType::Int:      return GL_INT;
		case Shaddock::ShaderDataType::Int2:     return GL_INT;
		case Shaddock::ShaderDataType::Int3:     return GL_INT;
		case Shaddock::ShaderDataType::Int4:     return GL_INT;
		case Shaddock::ShaderDataType::Bool:     return GL_BOOL;
		}

		SD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		SD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndexOffset);
			glVertexAttribPointer(m_VertexBufferIndexOffset,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndexOffset++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}