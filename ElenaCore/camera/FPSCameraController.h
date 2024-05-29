#pragma once

#include <unordered_map>
#include "Camera.h"
#include "FPSCamera.h"

namespace Elena
{
	class CFPSCameraController : public CCameraController
	{
	public:
		CFPSCameraController(const std::shared_ptr<CFPSCamera>& vFPSCamera);
		void processMouseMovement(float vXoffset, float vYoffset, bool vConstrainPitch = true) override;
		void processMouseScroll(float vYoffset) override;
		void processViewportSizeChange(int vWidth, int vHeight) override;
		void tick(float vDeltaTime) override;
	private:
		std::shared_ptr<CFPSCamera> m_pFPSCamera;
		std::unordered_map<int, CFPSCamera::ECameraMovement> m_KeyMappings;
	};
}