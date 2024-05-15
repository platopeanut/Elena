#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "base/Texture2D.h"

namespace Elena
{
	class CLight
	{
	public:
		enum class EShadowType
		{
			NO_SHADOW,
			HARD_SHADOW,
			SOFT_SHADOW
		};

		virtual glm::vec3 getColor() const = 0;
		virtual glm::vec3 getPosition() const = 0;
		virtual glm::vec3 getDirection() const = 0;
		virtual glm::mat4 getLightMatrix() const = 0;
		virtual EShadowType getShadowType() const = 0;
		virtual const std::shared_ptr<CTexture2D>& getShadowMap() const = 0;
	};
}