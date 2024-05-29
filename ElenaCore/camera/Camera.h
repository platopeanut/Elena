#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "base/FrameBuffer.h"

namespace Elena
{
	class CCamera
	{
	public:
		virtual glm::mat4 getViewMatrix() const = 0;
		virtual glm::mat4 getProjectionMatrix() const = 0;
		virtual glm::vec3 getClearColor() const = 0;
		virtual glm::vec3 getPosition() const = 0;
		virtual std::shared_ptr<CFrameBuffer> getFrameBuffer() const = 0;
	};

	class CCameraController
	{
	public:
		virtual void processMouseMovement(float vXoffset, float vYoffset, bool vConstrainPitch = true) {}
		virtual void processMouseScroll(float vYoffset) {}
		virtual void processViewportSizeChange(int vWidth, int vHeight) {}
		virtual void tick(float vDeltaTime) {}
	};
}