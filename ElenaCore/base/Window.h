#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Elena
{
	class CWindow
	{
	public:
		CWindow(unsigned int vWidth, unsigned int vHeight, const std::string& vWindowName);
		~CWindow();
		bool shouldClose() const;
		void swapBuffers() const;
		void pollEvents() const;
		unsigned int getWidth() const { return m_Width; }
		unsigned int getHeight() const { return m_Height; }
		// setWidth only be used for CElenaInput::__framebufferSizeCallback
		void setWidth(unsigned int vWidth) { m_Width = vWidth; }
		// setHeight only be used for CElenaInput::__framebufferSizeCallback
		void setHeight(unsigned int vHeight) { m_Height = vHeight; }
		float getAspect() const { return (float)m_Width / (float)m_Height; }
		GLFWwindow* getWindow() const { return m_pWindow; }
	private:
		unsigned int m_Width;
		unsigned int m_Height;
		GLFWwindow* m_pWindow;
	};
}