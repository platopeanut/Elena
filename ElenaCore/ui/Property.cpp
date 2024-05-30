#include "Property.h"
#include <imgui/imgui.h>

namespace Elena
{
	void CProperties::showGui() const
	{
		for (const auto& pProperty : m_Properties)
		{
			pProperty->showGui();
		}
	}

	void CProperties::setUniform(const std::shared_ptr<CShader>& vShader) const
	{
		for (const auto& pProperty : m_Properties)
		{
			pProperty->setUniform(vShader);
		}
	}

	bool CPropertyBool::showGui()
	{
		return ImGui::Checkbox(getName().c_str(), &m_Value);
	}

	bool CPropertyInt::showGui()
	{
		return ImGui::InputInt(getName().c_str(), &m_Value);
	}

	bool CPropertyFloat::showGui()
	{
		return ImGui::InputFloat(getName().c_str(), &m_Value);
	}

	bool CPropertyFloat3::showGui()
	{
		for (int i = 0; i < 3; ++i) m_RawValue[i] = m_Value[i];
		if (ImGui::InputFloat3(getName().c_str(), m_RawValue))
		{
			for (int i = 0; i < 3; ++i)
				m_Value[i] = m_RawValue[i];
			return true;
		}
		return false;
	}

	bool CPropertyFloat4::showGui()
	{
		for (int i = 0; i < 4; ++i) m_RawValue[i] = m_Value[i];
		if (ImGui::InputFloat4(getName().c_str(), m_RawValue))
		{
			for (int i = 0; i < 4; ++i)
				m_Value[i] = m_RawValue[i];
			return true;
		}
		return false;
	}
}
