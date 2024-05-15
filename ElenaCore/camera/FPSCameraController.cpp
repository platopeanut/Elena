#include "FPSCameraController.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/ElenaApp.h"

namespace Elena
{
	CFPSCameraController::CFPSCameraController(const std::shared_ptr<CFPSCamera>& vFPSCamera) :m_pFPSCamera(vFPSCamera) 
	{
		m_KeyMappings[GLFW_KEY_W] = CFPSCamera::ECameraMovement::FORWARD;
		m_KeyMappings[GLFW_KEY_S] = CFPSCamera::ECameraMovement::BACKWARD;
		m_KeyMappings[GLFW_KEY_A] = CFPSCamera::ECameraMovement::LEFT;
		m_KeyMappings[GLFW_KEY_D] = CFPSCamera::ECameraMovement::RIGHT;
		m_KeyMappings[GLFW_KEY_Q] = CFPSCamera::ECameraMovement::DOWN;
		m_KeyMappings[GLFW_KEY_E] = CFPSCamera::ECameraMovement::UP;
	}

	void CFPSCameraController::processMouseMovement(float vXoffset, float vYoffset, bool vConstrainPitch)
	{
		m_pFPSCamera->__processMouseMovement(vXoffset, vYoffset, vConstrainPitch);
	}

	void CFPSCameraController::processMouseScroll(float vYoffset)
	{
		m_pFPSCamera->__processMouseScroll(vYoffset);
	}

	void CFPSCameraController::processViewportSizeChange(float vAspect)
	{
		m_pFPSCamera->setAspect(vAspect);
	}

	void CFPSCameraController::tick(float vDeltaTime)
	{
		const auto& pWindow = CElenaApp::getInstance().getWindow();
		for (const auto& Pair : m_KeyMappings)
		{
			if (glfwGetKey(pWindow->getWindow(), Pair.first) == GLFW_PRESS)
				m_pFPSCamera->__processKeyboard(Pair.second, vDeltaTime);
		}
	}
}