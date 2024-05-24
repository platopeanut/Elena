#pragma once

#include <memory>
#include "base/Window.h"

namespace Elena
{
	class CWindowInput
	{
	public:
		CWindowInput(const std::shared_ptr<CWindow>& vWindow);
		void processInput(float vDeltaTime);
		bool getKeyDown(int vKeyCode);
	private:
		void __setWindowCallback();
		static void __framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight);
		static void __mouseCallback(GLFWwindow* vWindow, double vXposIn, double vYposIn);
		static void __scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset);
		std::shared_ptr<CWindow> m_pWindow;
	};
}