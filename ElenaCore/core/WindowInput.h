#pragma once

#include <memory>
#include <unordered_map>
#include "base/Window.h"
#include "core/WindowUI.h"

namespace Elena
{
	class CWindowInput
	{
	public:
		CWindowInput(const std::shared_ptr<CWindow>& vWindow, const std::shared_ptr<CWindowUI>& vWindowUI);
		~CWindowInput();
		bool getKeyDown(int vKeyCode) const;
		int getMouseButtonStatus(int vButton) const;
		void setCursorVisable(bool vVisible) const;
	private:
		void __setWindowCallback() const;
		static void __framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight);
		static void __mouseCallback(GLFWwindow* vWindow, double vXposIn, double vYposIn);
		static void __scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset);
		std::shared_ptr<CWindow> m_pWindow;
		static std::unordered_map<GLFWwindow*, CWindowUI*> m_WindowUIMap;
	};
}