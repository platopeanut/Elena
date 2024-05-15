#include "PhongMaterial.h"
#include "core/SceneManager.h"
#include "core/Node.h"
#include "utils/AssetsPath.h"

namespace Elena
{
	std::shared_ptr<CShader> CPhongMaterial::m_Shader{ nullptr };

	CPhongMaterial::CPhongMaterial(const std::shared_ptr<CTexture2D>& vDiffuseTexture, const std::shared_ptr<CTexture2D>& vSpecularTexture, float vShininess, bool vReceiveShadow)
		:m_pDiffuseTexture(vDiffuseTexture), m_pSpecularTexture(vSpecularTexture), m_Shininess(vShininess), m_ReceiveShadow(vReceiveShadow)
	{
		if (m_Shader == nullptr)
			m_Shader = std::make_shared<CShader>(
				CAssetsPath::getBuiltInShaderPath("material/phong.vert"),
				CAssetsPath::getBuiltInShaderPath("material/phong.frag")	
			);
	}

	void CPhongMaterial::use(const std::shared_ptr<CNode>& vNode) const
	{
		const auto& pCamera = CSceneManager::getInstance().getActiveScene()->getActiveCamera();
		const auto& Lights = CSceneManager::getInstance().getActiveScene()->getLights();
		_ASSERTE(Lights.size() > 0 && Lights[0] != nullptr);
		const auto& pMainLight = Lights[0];
		bool ReceiveShadow = m_ReceiveShadow;
		if (pMainLight->getShadowType() == CLight::EShadowType::NO_SHADOW) ReceiveShadow = false;
		m_Shader->use();
		m_Shader->setMat4("uModel", vNode->getModelMatrix());
		m_Shader->setMat4("uView", pCamera->getViewMatrix());
		m_Shader->setMat4("uProjection", pCamera->getProjectionMatrix());
		m_Shader->setMat4("uLightMatrix", pMainLight->getLightMatrix());

		m_Shader->setVec3("uViewPos", pCamera->getPosition());
		m_Shader->setBool("uReceiveShadow", ReceiveShadow);
		m_Shader->setFloat("uMaterial._Shininess", m_Shininess);
		m_Shader->setVec3("uLight._Direction", pMainLight->getDirection());
		m_Shader->setVec3("uLight._Ambient", pMainLight->getColor() * 0.2f);
		m_Shader->setVec3("uLight._Diffuse", pMainLight->getColor() * 0.5f);
		m_Shader->setVec3("uLight._Specular", pMainLight->getColor());

		glActiveTexture(GL_TEXTURE0);
		pMainLight->getShadowMap()->bind();
		glActiveTexture(GL_TEXTURE1);
		m_pDiffuseTexture->bind();
		glActiveTexture(GL_TEXTURE2);
		m_pSpecularTexture->bind();
		m_Shader->setInt("uShadowMap", 0);
		m_Shader->setInt("uMaterial._Diffuse", 1);
		m_Shader->setInt("uMaterial._Specular", 2);
	}
}