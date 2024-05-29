#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>

namespace Elena
{
	class CCommonWidgets
	{
	public:
		static bool showInputFloat3(const std::string& vLabelName, float* vInterValue, const glm::vec3& vCurrValue);
	};
}