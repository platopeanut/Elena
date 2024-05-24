#include "CheckerMaterial.h"
#include "core/SceneManager.h"
#include "utils/AssetsPath.h"

namespace Elena
{
	std::shared_ptr<CShader> CCheckerMaterial::m_pShader{ nullptr };

	CCheckerMaterial::CCheckerMaterial()
	{
		if (m_pShader == nullptr)
			m_pShader = std::make_shared<CShader>(
				CAssetsPath::getBuiltInShaderPath("material/checker.vert"),
				CAssetsPath::getBuiltInShaderPath("material/checker.frag"));
	}

	void CCheckerMaterial::use(const std::shared_ptr<CNode>& vNode) const
	{
		const auto& pCamera = CSceneManager::getInstance().getActiveScene()->getActiveCamera();
		m_pShader->use();
		m_pShader->setMat4("uModel", vNode->getModelMatrix());
		m_pShader->setMat4("uView", pCamera->getViewMatrix());
		m_pShader->setMat4("uProjection", pCamera->getProjectionMatrix());
	}
}