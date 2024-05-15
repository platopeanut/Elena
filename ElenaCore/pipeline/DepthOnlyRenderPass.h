#pragma once

#include "RenderPass.h"
#include "base/FrameBuffer.h"
#include "base/Shader.h"

namespace Elena
{
	class CDepthOnlyRenderPass : public CRenderPass
	{
	public:
		CDepthOnlyRenderPass();
		// Inherited via CRenderPass
		void render(const std::shared_ptr<CScene>& vScene) override;
	private:
		CFrameBuffer m_FrameBuffer;
		CShader m_Shader;
	};
}