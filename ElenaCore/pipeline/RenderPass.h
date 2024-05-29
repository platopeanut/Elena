#pragma once

#include "base/FrameBuffer.h"
#include "core/Scene.h"

namespace Elena
{
	class CRenderPass
	{
	public:
		virtual void render(const std::shared_ptr<CScene>& vScene) = 0;
		void setFrameBuffer(const std::shared_ptr<CFrameBuffer>& vFrameBuffer) { m_pFrameBuffer = vFrameBuffer; }
	protected:
		const std::shared_ptr<CFrameBuffer>& _getFrameBuffer(const std::shared_ptr<CScene>& vScene) const
		{
			if (m_pFrameBuffer != nullptr) return m_pFrameBuffer;
			return vScene->getActiveCamera()->getFrameBuffer();
		}
	private:
		std::shared_ptr<CFrameBuffer> m_pFrameBuffer;
	};
}