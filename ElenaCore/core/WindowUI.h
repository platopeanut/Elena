#pragma once

#include <memory>
#include <vector>
#include "base/Window.h"
#include "ui/Panel.h"

namespace Elena
{
	class CWindowUI
	{
	public:
		CWindowUI(const std::shared_ptr<CWindow>& vWindow);
		~CWindowUI();
		void init();
		void render(float vDeltaTime);
		void addPanel(const std::shared_ptr<CPanel>& vPanel);
		void onMouseMovement(float vXOffset, float vYOffset);
		void onMouseScroll(float vYOffset);
	private:
		void __renderStart() const;
		void __renderEnd() const;
		std::shared_ptr<CWindow> m_pWindow;
		std::vector<std::shared_ptr<CPanel>> m_Panels;
	};
}