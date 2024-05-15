#include "Window.h"
#include <spdlog/spdlog.h>

namespace Elena
{
	CWindow::CWindow(unsigned int vWidth, unsigned int vHeight, const std::string& vWindowName)
		: m_Width(vWidth), m_Height(vHeight), m_pWindow(nullptr)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_pWindow = glfwCreateWindow(m_Width, m_Height, vWindowName.c_str(), nullptr, nullptr);
		if (m_pWindow == nullptr)
		{
			spdlog::error("Failed to create GLFW window");
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_pWindow);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::error("Failed to initialize GLAD");
		}
	}

	CWindow::~CWindow()
	{
		glfwTerminate();
	}

	bool CWindow::shouldClose() const
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	void CWindow::swapBuffers() const
	{
		glfwSwapBuffers(m_pWindow);
	}

	void CWindow::pollEvents() const
	{
		glfwPollEvents();
	}
}