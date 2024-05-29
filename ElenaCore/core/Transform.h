#pragma once

#include <glm/glm.hpp>

namespace Elena
{
	class CTransform
	{
	public:
		CTransform(
			const glm::vec3& vPosition = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3 vRotation = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec3& vScale = glm::vec3(1.0f, 1.0f, 1.0f)
		);
		const glm::mat4& getModelMatrix() const { return m_ModelMatrix; }
		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getRotation() const { return m_Rotation; }
		const glm::vec3& getScale() const { return m_Scale; }
		void setPosition(const glm::vec3& vPosition);
		void setPosition(const float* vPosition);
		void setRotation(const glm::vec3& vRotation);
		void setRotation(const float* vRotation);
		void setScale(const glm::vec3& vScale);
		void setScale(const float* vScale);
	private:
		void __updateModelMatrix();
		glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Rotation; // Euler Degree
		glm::vec3 m_Scale;
	};
}