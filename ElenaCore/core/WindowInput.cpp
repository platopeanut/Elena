#include "WindowInput.h"
#include "ElenaApp.h"
#include "SceneManager.h"

namespace Elena
{
	CWindowInput::CWindowInput(const std::shared_ptr<CWindow>& vWindow) :m_pWindow(vWindow)
	{
		__setWindowCallback();
	}

	void CWindowInput::processInput(float vDeltaTime)
	{
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		
		if (glfwGetKey(m_pWindow->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_pWindow->getWindow(), true);

		pCameraController->tick(vDeltaTime);
	}

	bool CWindowInput::getKeyDown(int vKeyCode)
	{
		return glfwGetKey(m_pWindow->getWindow(), vKeyCode) == GLFW_PRESS;
	}

	void CWindowInput::__setWindowCallback()
	{
		glfwSetFramebufferSizeCallback(m_pWindow->getWindow(), __framebufferSizeCallback);
		glfwSetCursorPosCallback(m_pWindow->getWindow(), __mouseCallback);
		glfwSetScrollCallback(m_pWindow->getWindow(), __scrollCallback);
		//glfwSetInputMode(pWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void CWindowInput::__framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight)
	{
		
		glViewport(0, 0, vWidth, vHeight);
		const auto& pWindow = CWindow::getWindowByNative(vWindow);
		pWindow->setWidth(vWidth);
		pWindow->setHeight(vHeight);
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		pCameraController->processViewportSizeChange(pWindow->getAspect());
	}

	void CWindowInput::__mouseCallback(GLFWwindow* vWindow, double vXposIn, double vYposIn)
	{
		static float LastX = 0.0f;
		static float LastY = 0.0f;
		static bool IsFirstMouse = true;
		
		float Xpos = static_cast<float>(vXposIn);
		float Ypos = static_cast<float>(vYposIn);

		if (IsFirstMouse)
		{
			LastX = Xpos;
			LastY = Ypos;
			IsFirstMouse = false;
		}

		float Xoffset = Xpos - LastX;
		float Yoffset = LastY - Ypos;

		LastX = Xpos;
		LastY = Ypos;

		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		pCameraController->processMouseMovement(Xoffset, Yoffset);
	}

	void CWindowInput::__scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset)
	{
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		pCameraController->processMouseScroll(static_cast<float>(vYoffset));
	}
}