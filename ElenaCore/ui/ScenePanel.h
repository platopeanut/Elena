#pragma once

#include "Panel.h"
#include "core/WindowInput.h"
#include "core/SceneManager.h"

namespace Elena
{
	class CScenePanel : public CPanel
	{
	public:
		CScenePanel(const std::shared_ptr<CWindowInput>& vWindowInput, int vWidth, int vHeight);
		// Inherited via CPanel
		void init() override;
		void render(float vDeltaTime) override;
		void onMouseMovement(float vXOffset, float vYOffset) override;
		void onMouseScroll(float vYOffset) override;
	private:
		void __processInput(float vDeltaTime);
		bool __updateCameraViewport();
		int m_Width;
		int m_Height;
		bool m_IsFocused;
		bool m_TodoDefocusd;
		std::shared_ptr<CWindowInput> m_pWindowInput;
		std::shared_ptr<CCameraController> m_pCameraController;
	};
}

