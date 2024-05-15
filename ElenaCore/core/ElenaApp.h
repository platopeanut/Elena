#pragma once

#include <memory>
#include <functional>
#include "base/Window.h"

namespace Elena
{
	class CElenaApp
	{
	public:
		static CElenaApp& getInstance();
		void setMainWindow(const std::shared_ptr<CWindow>& vWindow);
		const std::shared_ptr<CWindow>& getWindow() const;
		void run(std::function<void()> vTickFunc);
		void setUI(std::function<void()> vUiFunc);
	private:
		CElenaApp();
		~CElenaApp();
		CElenaApp(const CElenaApp&) = delete;
		CElenaApp& operator=(const CElenaApp&) = delete;
		std::shared_ptr<CWindow> m_pWindow;
		float m_DeltaTime;
		std::function<void()> m_pUiFunc;
	};
}