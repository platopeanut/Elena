#include "BlankMaterial.h"
#include "core/Node.h"
#include "core/SceneManager.h"
#include "utils/AssetsPath.h"

namespace Elena
{
	std::shared_ptr<CShader> CBlankMaterial::m_pShader{ nullptr };

	CBlankMaterial::CBlankMaterial()
	{
		if (m_pShader == nullptr)
			m_pShader = std::make_shared<CShader>(
				CAssetsPath::getBuiltInShaderPath("material/blank.vert"),
				CAssetsPath::getBuiltInShaderPath("material/blank.frag"));
		m_Properties.addProperty(std::make_shared<CPropertyColor>("uDiffuseColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
	}

	void CBlankMaterial::use(const std::shared_ptr<CNode>& vNode) const
	{
		const auto& pCamera = CSceneManager::getInstance().getActiveScene()->getActiveCamera();
		const auto& pMainLight = CSceneManager::getInstance().getActiveScene()->getLights()[0];
		m_pShader->use();
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", pCamera->getViewMatrix());
		m_pShader->setUniform("uProjection", pCamera->getProjectionMatrix());
		m_pShader->setUniform("uLightDirection", pMainLight->getDirection());
		m_pShader->setUniform("uLightColor", pMainLight->getColor());
		m_Properties.setUniform(m_pShader);
	}
}