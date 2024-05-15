#include "ElenaApp.h"
#include <spdlog/spdlog.h>
#include "ElenaInput.h"
#include "ElenaUI.h"
#include "SceneManager.h"
#include "primitive/Primitive.h"

namespace Elena
{
	CElenaApp& CElenaApp::getInstance()
	{
		static CElenaApp App;
		return App;
	}

	void CElenaApp::setMainWindow(const std::shared_ptr<CWindow>& vWindow)
	{
		m_pWindow = vWindow;
		CElenaInput::setWindowCallback();
		CElenaUI::init();
	}

	const std::shared_ptr<CWindow>& CElenaApp::getWindow() const
	{
		_ASSERTE(m_pWindow != nullptr);
		return m_pWindow;
	}

	void CElenaApp::run(std::function<void()> vTickFunc)
	{
		spdlog::info("Start Render :)");
		float LastFrame = 0.0f;
		while (!m_pWindow->shouldClose())
		{
			float CurrentFrame = static_cast<float>(glfwGetTime());
			m_DeltaTime = CurrentFrame - LastFrame;
			LastFrame = CurrentFrame;
			CElenaInput::processInput(m_DeltaTime);
			vTickFunc();
			CElenaUI::renderStart();
			if (m_pUiFunc != nullptr) m_pUiFunc();
			CElenaUI::renderEnd();
			m_pWindow->swapBuffers();
			m_pWindow->pollEvents();
		}
	}

	void CElenaApp::setUI(std::function<void()> vUiFunc)
	{
		m_pUiFunc = std::move(vUiFunc);
	}

	CElenaApp::CElenaApp() : m_pWindow(nullptr), m_DeltaTime(0.0f), m_pUiFunc(nullptr) {}
	
	CElenaApp::~CElenaApp()
	{
		CPrimitive::clear();
		CElenaUI::destroy();
	}
}