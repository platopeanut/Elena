#pragma once

#include <string>

namespace Elena
{
	class CPanel
	{
	public:
		virtual void init() {}
		virtual void render(float vDeltaTime) = 0;
		virtual bool catchEvent() const { return m_isCatchEvent; }
		virtual void onMouseMovement(float vXOffset, float vYOffset) {}
		virtual void onMouseScroll(float vYoffset) {}
	protected:
		bool m_isCatchEvent = false;
	};
}