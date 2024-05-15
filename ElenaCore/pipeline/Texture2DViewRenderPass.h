#pragma once

#include "RenderPass.h"
#include "base/Texture2D.h"
#include "base/VertexBuffer.h"
#include "base/Shader.h"

namespace Elena
{
	class CTexture2DViewRenderPass : public CRenderPass
	{
	public:
		CTexture2DViewRenderPass(const std::shared_ptr<CTexture2D>& vTexture2D);
		void setTexture2D(const std::shared_ptr<CTexture2D>& vTexture2D) { m_pTexture2D = vTexture2D; }
		// Inherited via CRenderPass
		void render(const std::shared_ptr<CScene>& vScene) override;
	private:
		std::shared_ptr<CTexture2D> m_pTexture2D;
		std::shared_ptr<CVertexBuffer> m_pQuadVertexBuffer;
		CShader m_Shader;
	};
}