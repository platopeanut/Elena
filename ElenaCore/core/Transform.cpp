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

	void CTransform::setPosition(const float* vPosition)
	{
		setPosition(glm::vec3(vPosition[0], vPosition[1], vPosition[2]));
	}

	void CTransform::setRotation(const glm::vec3& vRotation)
	{
		m_Rotation = vRotation;
		__updateModelMatrix();
	}

	void CTransform::setRotation(const float* vRotation)
	{
		setRotation(glm::vec3(vRotation[0], vRotation[1], vRotation[2]));
	}

	void CTransform::setScale(const glm::vec3& vScale)
	{
		m_Scale = vScale;
		__updateModelMatrix();
	}

	void CTransform::setScale(const float* vScale)
	{
		setScale(glm::vec3(vScale[0], vScale[1], vScale[2]));
	}

	void CTransform::__updateModelMatrix()
	{
		// T * R * S
		glm::vec3 RotationRadians = glm::radians(m_Rotation);
		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
		// rotate ZXY (Right-Hand, Y up)
		m_ModelMatrix = glm::rotate(m_ModelMatrix, RotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, RotationRadians.x, glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, RotationRadians.y, glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
	}
}