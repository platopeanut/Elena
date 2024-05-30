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
		m_Properties.addProperty(std::make_shared<CPropertyFloat4>("uTexST", glm::vec4(1.0f, 1.0f, 0.0f, 0.0f)));
	}

	void CCheckerMaterial::use(const std::shared_ptr<CNode>& vNode) const
	{
		const auto& pCamera = CSceneManager::getInstance().getActiveScene()->getActiveCamera();
		m_pShader->use();
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", pCamera->getViewMatrix());
		m_pShader->setUniform("uProjection", pCamera->getProjectionMatrix());
		m_Properties.setUniform(m_pShader);
	}
}