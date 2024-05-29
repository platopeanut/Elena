#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

namespace Elena
{
	class CFPSCamera : public CCamera
	{
	public:
		enum class ECameraMovement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};
	public:
		CFPSCamera(const glm::vec3& vPosition = glm::vec3(0.0f, 0.0f, 0.0f), float vNear = 0.1f, float vFar = 100.0f);
		// Inherited via CCamera
		glm::mat4 getViewMatrix() const override;
		glm::mat4 getProjectionMatrix() const override;
		glm::vec3 getClearColor() const override { return m_ClearColor; }
		glm::vec3 getPosition() const override { return m_Position; }
		std::shared_ptr<CFrameBuffer> getFrameBuffer() const override { return m_pFrameBuffer; }
		void setAspect(float vAspect) { m_Aspect = vAspect; }
	private:
		friend class CFPSCameraController;
		void __processKeyboard(ECameraMovement vDirection, float vDeltaTime);
		void __processMouseMovement(float vXoffset, float vYoffset, bool vConstrainPitch = true);
		void __processMouseScroll(float vYoffset);
		void __updateCameraVectors();
		void __updateViewport(int vWidth, int vHeight);

		std::shared_ptr<CFrameBuffer> m_pFrameBuffer;
		// camera Attributes
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		// euler Angles
		float m_Yaw;
		float m_Pitch;
		// camera options
		float m_MovementSpeed;
		float m_MouseSensitivity;
		float m_Zoom;
		// projection
		float m_Aspect;
		float m_Near;
		float m_Far;
		// other settings
		glm::vec3 m_ClearColor;
	};
}