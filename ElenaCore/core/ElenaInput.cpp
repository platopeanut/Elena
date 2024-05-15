#include "ElenaInput.h"
#include "ElenaApp.h"
#include "SceneManager.h"

namespace Elena
{	
	void CElenaInput::processInput(float vDeltaTime)
	{
		const auto& pWindow = CElenaApp::getInstance().getWindow();
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		
		if (glfwGetKey(pWindow->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(pWindow->getWindow(), true);

		pCameraController->tick(vDeltaTime);
	}

	void CElenaInput::setWindowCallback()
	{
		const auto& pWindow = CElenaApp::getInstance().getWindow();
		glfwSetFramebufferSizeCallback(pWindow->getWindow(), __framebufferSizeCallback);
		glfwSetCursorPosCallback(pWindow->getWindow(), __mouseCallback);
		glfwSetScrollCallback(pWindow->getWindow(), __scrollCallback);
		//glfwSetInputMode(pWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	bool CElenaInput::getKeyDown(int vKeyCode)
	{
		const auto& pWindow = CElenaApp::getInstance().getWindow();
		return glfwGetKey(pWindow->getWindow(), vKeyCode) == GLFW_PRESS;
	}

	void CElenaInput::__framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight)
	{
		glViewport(0, 0, vWidth, vHeight);
		const auto& pWindow = CElenaApp::getInstance().getWindow();
		pWindow->setWidth(vWidth);
		pWindow->setHeight(vHeight);
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		pCameraController->processViewportSizeChange(pWindow->getAspect());
	}

	void CElenaInput::__mouseCallback(GLFWwindow* vWindow, double vXposIn, double vYposIn)
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

	void CElenaInput::__scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset)
	{
		const auto& pCameraController = CSceneManager::getInstance().getActiveScene()->getActiveCameraController();
		pCameraController->processMouseScroll(static_cast<float>(vYoffset));
	}
}