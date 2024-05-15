#include "BlankMaterial.h"
#include "core/Node.h"
#include "core/SceneManager.h"
#include "utils/AssetsPath.h"

namespace Elena
{
	std::shared_ptr<CShader> CBlankMaterial::m_Shader{ nullptr };

	CBlankMaterial::CBlankMaterial()
	{
		if (m_Shader == nullptr)
			m_Shader = std::make_shared<CShader>(
				CAssetsPath::getBuiltInShaderPath("material/blank.vert"),
				CAssetsPath::getBuiltInShaderPath("material/blank.frag"));
	}

	void CBlankMaterial::use(const std::shared_ptr<CNode>& vNode) const
	{
		const auto& pCamera = CSceneManager::getInstance().getActiveScene()->getActiveCamera();
		const auto& pMainLight = CSceneManager::getInstance().getActiveScene()->getLights()[0];
		m_Shader->use();
		m_Shader->setMat4("uModel", vNode->getModelMatrix());
		m_Shader->setMat4("uView", pCamera->getViewMatrix());
		m_Shader->setMat4("uProjection", pCamera->getProjectionMatrix());
		m_Shader->setVec3("uLightDirection", pMainLight->getDirection());
		m_Shader->setVec3("uLightColor", pMainLight->getColor());
	}
}