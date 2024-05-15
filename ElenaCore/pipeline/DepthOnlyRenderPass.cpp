#include "DepthOnlyRenderPass.h"
#include <queue>
#include <spdlog/spdlog.h>
#include "utils/AssetsPath.h"

namespace Elena
{
	CDepthOnlyRenderPass::CDepthOnlyRenderPass()
		:m_FrameBuffer{}, m_Shader(CAssetsPath::getBuiltInShaderPath("depthOnly.vert"), CAssetsPath::getBuiltInShaderPath("depthOnly.frag"))
	{

		m_FrameBuffer.bind();
		CFrameBuffer::setColorBufferEmpty();
		//CFrameBuffer::check(); // miss depth buffer
	}

	void CDepthOnlyRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		m_FrameBuffer.bind();
		m_Shader.use();
		for (const auto& pLight : vScene->getLights())
		{
			if (pLight->getShadowType() == CLight::EShadowType::NO_SHADOW)
				continue;
			const auto& pShadowMap = pLight->getShadowMap();
			CFrameBuffer::setAttachmentTexture2D(GL_DEPTH_ATTACHMENT, pShadowMap->getTextureID());
			CFrameBuffer::check();

			glViewport(0, 0, pShadowMap->getWidth(), pShadowMap->getHeight());
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);

			m_Shader.setMat4("uLightMatrix", pLight->getLightMatrix());

			std::queue<std::shared_ptr<CNode>> Queue;
			Queue.push(vScene->getRootNode());
			while (!Queue.empty())
			{
				const auto& pNode = Queue.front();
				Queue.pop();

				for (const auto& pMesh : pNode->getMeshList())
				{
					m_Shader.setMat4("uModel", pNode->getModelMatrix());
					pMesh->getVertexBuffer()->draw();
				}
				for (const auto& pChildNode : pNode->getChildNodes())
				{
					Queue.push(pChildNode);
				}
			}
		}
	}
}