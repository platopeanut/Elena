#pragma once

struct GLFWwindow;

namespace Elena
{
	class CElenaInput
	{
	public:
		static void processInput(float vDeltaTime);
		static void setWindowCallback();
		static bool getKeyDown(int vKeyCode);
	private:
		CElenaInput() = delete;
		CElenaInput(const CElenaInput&) = delete;
		CElenaInput& operator=(const CElenaInput&) = delete;

		static void __framebufferSizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight);
		static void __mouseCallback(GLFWwindow* vWindow, double vXposIn, double vYposIn);
		static void __scrollCallback(GLFWwindow* vWindow, double vXoffset, double vYoffset);
	};
}