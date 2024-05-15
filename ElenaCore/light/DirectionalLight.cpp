#include "DirectionalLight.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Elena
{
	CDirectionalLight::CDirectionalLight(const glm::vec3& vPosition, const glm::vec3& vDirection, float vAreaWidth, float vAreaHeight)
		:m_Position(vPosition), m_Direction(vDirection), m_AreaWidth(vAreaWidth), m_AreaHeight(vAreaHeight),
		m_LightColor(1.0f, 1.0f, 1.0f),
		m_ShadowType(CLight::EShadowType::HARD_SHADOW), 
		m_pShadowMap(std::make_shared<CTexture2D>(2048, 2048, 1, GL_DEPTH_COMPONENT, GL_FLOAT))
	{
		m_pShadowMap->bind();
		CTexture2D::setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		CTexture2D::setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		CTexture2D::setParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		CTexture2D::setParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		GLfloat BorderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		CTexture2D::setParameters(GL_TEXTURE_BORDER_COLOR, BorderColor);
	}

	glm::mat4 CDirectionalLight::getLightMatrix() const
	{
		glm::mat4 ViewMatrix = glm::lookAt(m_Position, m_Position + m_Direction, glm::vec3(0.0, 1.0, 0.0));
		float HalfWidth = m_AreaWidth * 0.5f;
		float HalfHeight = m_AreaHeight * 0.5f;
		glm::mat4 ProjectionMatrix = glm::ortho(-HalfWidth, HalfWidth, -HalfHeight, HalfHeight, 0.1f, 100.0f);
		return ProjectionMatrix * ViewMatrix;
	}
}