#include "Texture2DViewRenderPass.h"
#include "base/FrameBuffer.h"
#include "core/ElenaApp.h"
#include "primitive/Primitive.h"
#include "utils/AssetsPath.h"

namespace Elena
{
	CTexture2DViewRenderPass::CTexture2DViewRenderPass(const std::shared_ptr<CTexture2D>& vTexture2D)
		:m_pTexture2D(vTexture2D), m_pQuadVertexBuffer(CPrimitive::createQuad()),
		m_Shader(CAssetsPath::getBuiltInShaderPath("tex2Dview.vert"), CAssetsPath::getBuiltInShaderPath("tex2Dview.frag"))
	{
	}

	void CTexture2DViewRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		//CFrameBuffer::bindDefaultFrameBuffer();
		const auto& pFrameBuffer = _getFrameBuffer(vScene);
		pFrameBuffer->bind();
		pFrameBuffer->updateViewport();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture2D->bind();
		m_Shader.use();
		m_Shader.setUniform("uTexture", 0);
		m_Shader.setUniform("uChannels", m_pTexture2D->getChannels());

		m_pQuadVertexBuffer->draw();
	}
}