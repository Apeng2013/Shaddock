#include "sdpch.h"

#include "Shaddock/Renderer/OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"


namespace Shaddock {
	OrthographicCamera::OrthographicCamera(float left, float right, float buttom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, buttom, top, -1.f, 1.f)), m_ViewMatrix(1.0f)
	{
		SD_PROFILE_FUNCTION();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float buttom, float top)
	{
		SD_PROFILE_FUNCTION();
		m_ProjectionMatrix = glm::ortho(left, right, buttom, top, -1.f, 1.f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		SD_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}