#include "ElenaApp.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>
#include "SceneManager.h"
#include "ui/ScenePanel.h"
#include "ui/InspectorPanel.h"
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
		m_pWindowUI = std::make_shared<CWindowUI>(vWindow);
		m_pWindowInput = std::make_shared<CWindowInput>(vWindow, m_pWindowUI);
		m_pWindowUI->addPanel(std::make_shared<CScenePanel>(m_pWindowInput, vWindow->getWidth(), vWindow->getHeight()));
		m_pWindowUI->addPanel(std::make_shared<CInspectorPanel>());
	}

	void CElenaApp::run()
	{
		__init();
		spdlog::info("Start Render :)");
		float LastFrame = 0.0f;
		while (!m_pWindow->shouldClose())
		{
			float CurrentFrame = static_cast<float>(glfwGetTime());
			m_DeltaTime = CurrentFrame - LastFrame;
			LastFrame = CurrentFrame;
			m_pRenderFunc();
			m_pWindowUI->render(m_DeltaTime);
			m_pWindow->swapBuffers();
			m_pWindow->pollEvents();
		}
	}

	void CElenaApp::setRender(std::function<void()> vRenderFunc)
	{
		m_pRenderFunc = std::move(vRenderFunc);
	}

	CElenaApp::CElenaApp() : m_pWindow(nullptr), m_DeltaTime(0.0f) {}
	
	CElenaApp::~CElenaApp()
	{
		CPrimitive::clear();
	}

	void CElenaApp::__init()
	{
		m_pWindowUI->init();
	}
}