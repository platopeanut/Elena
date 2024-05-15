#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Elena
{
	CTransform::CTransform(const glm::vec3& vPosition, const glm::vec3 vRotation, const glm::vec3& vScale)
		:m_Position(vPosition), m_Rotation(vRotation), m_Scale(vScale)
	{
		__updateModelMatrix();
	}

	void CTransform::setPosition(const glm::vec3& vPosition)
	{
		m_Position = vPosition;
		__updateModelMatrix();
	}

	void CTransform::setScale(const glm::vec3& vScale)
	{
		m_Scale = vScale;
		__updateModelMatrix();
	}

	void CTransform::__updateModelMatrix()
	{
		// T * R * S
		glm::vec3 RotationRadians = glm::radians(m_Rotation);
		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
		// rotate todo
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	}
}