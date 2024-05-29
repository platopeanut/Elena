#include "CommonWidgets.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

namespace Elena
{
	bool CCommonWidgets::showInputFloat3(const std::string& vLabelName, float* vInterValue, const glm::vec3& vCurrValue)
	{
		vInterValue[0] = vCurrValue[0];
		vInterValue[1] = vCurrValue[1];
		vInterValue[2] = vCurrValue[2];
		return ImGui::InputFloat3(vLabelName.c_str(), vInterValue);
	}
}