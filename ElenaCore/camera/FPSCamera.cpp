#include "FPSCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Elena
{
	CFPSCamera::CFPSCamera(float vAspect, const glm::vec3& vPosition, float vNear, float vFar)
		:m_Position(vPosition), m_Front(0.0f, 0.0f, -1.0f), m_Up(0.0f, 1.0f, 0.0f), m_Right{}, m_WorldUp{},
		m_Yaw(-90.0f), m_Pitch(0.0f),
		m_MovementSpeed(2.5f), m_MouseSensitivity(0.1f), m_Zoom(45.0f),
		m_Aspect(vAspect), m_Near(vNear), m_Far(vFar),
		m_ClearColor(0.2f, 0.3f, 0.47f)
	{
		m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		__updateCameraVectors();
	}

	glm::mat4 CFPSCamera::getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	glm::mat4 CFPSCamera::getProjectionMatrix() const
	{
		return glm::perspective(m_Zoom, m_Aspect, m_Near, m_Far);
	}

	void CFPSCamera::__processKeyboard(ECameraMovement vDirection, float vDeltaTime)
	{
		float Velocity = m_MovementSpeed * vDeltaTime;
		if (vDirection == ECameraMovement::FORWARD)
			m_Position += m_Front * Velocity;
		if (vDirection == ECameraMovement::BACKWARD)
			m_Position -= m_Front * Velocity;
		if (vDirection == ECameraMovement::LEFT)
			m_Position -= m_Right * Velocity;
		if (vDirection == ECameraMovement::RIGHT)
			m_Position += m_Right * Velocity;
		if (vDirection == ECameraMovement::UP)
			m_Position += m_WorldUp * Velocity;
		if (vDirection == ECameraMovement::DOWN)
			m_Position -= m_WorldUp * Velocity;
	}

	void CFPSCamera::__processMouseMovement(float vXoffset, float vYoffset, bool vConstrainPitch)
	{
		vXoffset *= m_MouseSensitivity;
		vYoffset *= m_MouseSensitivity;

		m_Yaw += vXoffset;
		m_Pitch += vYoffset;

		if (vConstrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}

		__updateCameraVectors();
	}

	void CFPSCamera::__processMouseScroll(float vYoffset)
	{
		m_Zoom -= (float)vYoffset;
		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 45.0f)
			m_Zoom = 45.0f;
	}

	void CFPSCamera::__updateCameraVectors()
	{
		glm::vec3 Front{};
		Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		Front.y = sin(glm::radians(m_Pitch));
		Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		
		m_Front = glm::normalize(Front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}