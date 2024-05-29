#include "InspectorPanel.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

namespace Elena
{
	void CInspectorPanel::render(float vDeltaTime)
	{
		ImGui::Begin("Inspector");
		if (ImGui::Button("Hello ImGUI"))
		{
			spdlog::info("Clicked Once!");
		}
		ImGui::End();
	}
}