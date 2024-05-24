#pragma once

#include <memory>
#include "base/Window.h"

namespace Elena
{
	class CWindowUI
	{
	public:
		CWindowUI(const std::shared_ptr<CWindow>& vWindow);
		void init();
		void renderStart();
		void renderEnd();
		void destroy();
	private:
		std::shared_ptr<CWindow> m_pWindow;
	};
}