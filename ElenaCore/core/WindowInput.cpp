#include "WindowInput.h"

namespace Elena
{
	std::unordered_map<GLFWwindow*, CWindowUI*> CWindowInput::m_WindowUIMap;

	CWindowInput::CWindowInput(const std::shared_ptr<CWindow>& vWindow, const std::shared_ptr<CWindowUI>& vWindowUI)
		:m_pWindow(vWindow)
	{
		m_WindowUIMap[vWindow->getWindow()] = vWindowUI.get();
		__setWindowCallback();
	}

	CWindowInput::~CWindowInput()
	{
		m_WindowUIMap.erase(m_pWindow->getWindow());
	}

	bool CWindowInput::getKeyDown(int vKeyCode) const
	{
		return glfwGetKey(m_pWindow->getWindow(), vKeyCode) == GLFW_PRESS;
	}

	int CWindowInput::getMouseButtonStatus(int vButton) const
	{
		return glfwGetMouseButton(m_pWindow->getWindow(), vButton);
	}

	void CWindowInput::setCursorVisable(bool vVisible) const
	{
		glfwSetInputMode(m_pWindow->getWindow(), GLFW_CURSOR, vVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}

	void CWindowInput::__setWindowCallback() const
	{
		glfwSetFramebufferSizeCallback(m_pWindow->getWindow(), __framebufferSizeCallback);
		glfwSetCursorPosCallback(m_pWindow->getWindow(), __mouseCallback);
		glfwSetScrollCallback(m_pWindow->getWindow(), __scrollCallback);
	}

	void CWindowInput::__framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight)
	{

		glViewport(0, 0, vWidth, vHeight);
		const auto& pWindow = CWindow::getWindowByNative(vWindow);
		pWindow->setWidth(vWidth);
		pWindow->setHeight(vHeight);
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

		m_WindowUIMap[vWindow]->onMouseMovement(Xoffset, Yoffset);
	}

	void CWindowInput::__scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset)
	{
		m_WindowUIMap[vWindow]->onMouseScroll(static_cast<float>(vYoffset));
	}
}