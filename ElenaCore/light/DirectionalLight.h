#pragma once

#include "Light.h"

namespace Elena
{
	class CDirectionalLight : public CLight
	{
	public:
		CDirectionalLight(const glm::vec3& vPosition, const glm::vec3& vDirection, float vAreaWidth, float vAreaHeight);
		// Inherited via CLight
		glm::vec3 getPosition() const override { return m_Position; }
		glm::vec3 getDirection() const override { return m_Direction; }
		glm::vec3 getColor() const override { return m_LightColor; }
		EShadowType getShadowType() const override { return m_ShadowType; }
		const std::shared_ptr<CTexture2D>& getShadowMap() const override { return m_pShadowMap; }
		glm::mat4 getLightMatrix() const override;
		void setColor(const glm::vec3& vColor) override { m_LightColor = vColor; }
		void setPosition(const glm::vec3& vPosition) override { m_Position = vPosition; }
		void setDirection(const glm::vec3& vDirection) override { m_Direction = vDirection; }
		void setShadowType(EShadowType vShadowType) override { m_ShadowType = vShadowType; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		float m_AreaWidth;
		float m_AreaHeight;
		glm::vec3 m_LightColor;
		EShadowType m_ShadowType;
		std::shared_ptr<CTexture2D> m_pShadowMap;
	};
}
