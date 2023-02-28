#pragma once

#include "glm/glm.hpp"
namespace Shaddock {
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float buttom, float top);

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() { return m_Position; }

		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		float GetRotation() { return m_Rotation; }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}