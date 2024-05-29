#include "ScenePanel.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

namespace Elena
{
	CScenePanel::CScenePanel(const std::shared_ptr<CWindowInput>& vWindowInput, int vWidth, int vHeight)
		:m_pWindowInput(vWindowInput), m_pCameraController(nullptr),
		m_Width(vWidth), m_Height(vHeight), m_IsFocused(false), m_TodoDefocusd(false)
	{
		m_isCatchEvent = true;
	}

	void CScenePanel::init()
	{
		m_pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		m_pCameraController->processViewportSizeChange(m_Width, m_Height);
	}

	void CScenePanel::render(float vDeltaTime)
	{
		const auto& pScene = Elena::CSceneManager::getInstance().getActiveScene();
		const auto& pFrameBuffer = pScene->getActiveCamera()->getFrameBuffer();
		auto TexID = pFrameBuffer->getTexture2D(GL_COLOR_ATTACHMENT0)->getTextureID();

		__processInput(vDeltaTime);
		static bool IsFirstRender = true;
		if (IsFirstRender)
		{
			IsFirstRender = false;
			ImGui::SetNextWindowSize(ImVec2(pFrameBuffer->getWidth(), pFrameBuffer->getHeight()));
		}
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse);
		if (m_TodoDefocusd)
		{
			m_TodoDefocusd = false;
			ImGui::SetNextWindowFocus();
		}
		m_IsFocused = ImGui::IsWindowFocused();
		m_pWindowInput->setCursorVisable(!m_IsFocused);
		if (!__updateCameraViewport())
		{
			ImGui::Image((void*)TexID, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
	}

	void CScenePanel::onMouseMovement(float vXOffset, float vYOffset)
	{
		if (!m_IsFocused || m_pCameraController == nullptr) return;
		m_pCameraController->processMouseMovement(vXOffset, vYOffset);
	}

	void CScenePanel::onMouseScroll(float vYOffset)
	{
		if (!m_IsFocused || m_pCameraController == nullptr) return;
		m_pCameraController->processMouseScroll(vYOffset);
	}

	void CScenePanel::__processInput(float vDeltaTime)
	{
		if (m_pWindowInput->getKeyDown(GLFW_KEY_ESCAPE))
			m_TodoDefocusd = true;
		if (!m_IsFocused || m_pCameraController == nullptr) return;
		m_pCameraController->tick(vDeltaTime);
	}

	bool CScenePanel::__updateCameraViewport()
	{
		ImVec2 PanelSize = ImGui::GetContentRegionAvail();
		if (PanelSize.x == m_Width && PanelSize.y == m_Height) return false;
		if (PanelSize.x <= 0 && PanelSize.y <= 0) return false;
		if (m_pWindowInput->getMouseButtonStatus(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) return false;
		m_Width = PanelSize.x;
		m_Height = PanelSize.y;
		m_pCameraController->processViewportSizeChange(m_Width, m_Height);
		return true;
	}
}