#include "BaseRenderPass.h"
#include <queue>
#include <spdlog/spdlog.h>
#include "base/FrameBuffer.h"
#include "core/ElenaApp.h"

namespace Elena
{
	void CBaseRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		//CFrameBuffer::bindDefaultFrameBuffer();
		const auto& pFrameBuffer = _getFrameBuffer(vScene);
		pFrameBuffer->bind();
		pFrameBuffer->updateViewport();
		glEnable(GL_DEPTH_TEST);
		const auto& ClearColor = vScene->getActiveCamera()->getClearColor();
		glClearColor(ClearColor.x, ClearColor.y, ClearColor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const auto& pRootNode = vScene->getRootNode();
		if (pRootNode == nullptr) return;
		std::queue<std::shared_ptr<CNode>> Queue;
		Queue.push(pRootNode);
		while (!Queue.empty())
		{
			const auto& pNode = Queue.front();
			Queue.pop();
			for (const auto& pMesh : pNode->getMeshList())
			{
				pMesh->getMaterial()->use(pNode);
				pMesh->getVertexBuffer()->draw();
			}
			for (const auto& pChildNode : pNode->getChildNodes())
				Queue.push(pChildNode);
		}
	}
}
