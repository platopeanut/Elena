#pragma once

#include <memory>
#include <functional>
#include "base/Window.h"
#include "WindowUI.h"
#include "WindowInput.h"

namespace Elena
{
	class CElenaApp
	{
	public:
		static CElenaApp& getInstance();
		void setMainWindow(const std::shared_ptr<CWindow>& vWindow);
		const std::shared_ptr<CWindow>& getWindow() const
		{
			_ASSERTE(m_pWindow != nullptr);
			return m_pWindow;
		}
		void run();
		void setRender(std::function<void()> vRenderFunc);
	private:
		CElenaApp();
		~CElenaApp();
		CElenaApp(const CElenaApp&) = delete;
		CElenaApp& operator=(const CElenaApp&) = delete;
		void __init();
		std::shared_ptr<CWindow> m_pWindow;
		std::shared_ptr<CWindowInput> m_pWindowInput;
		std::shared_ptr<CWindowUI> m_pWindowUI;
		float m_DeltaTime;
		std::function<void()> m_pRenderFunc;
	};
}