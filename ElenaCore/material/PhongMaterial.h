#pragma once

#include <memory>
#include "Material.h"
#include "base/Shader.h"
#include "base/Texture2D.h"

namespace Elena
{
	class CPhongMaterial : public CMaterial
	{
	public:
		CPhongMaterial(
			const std::shared_ptr<CTexture2D>& vDiffuseTexture,
			const std::shared_ptr<CTexture2D>& vSpecularTexture,
			float vShininess,
			bool vReceiveShadow = true
		);
		// Inherited via CMaterial
		void use(const std::shared_ptr<CNode>& vNode) const override;
	private:
		std::shared_ptr<CTexture2D> m_pDiffuseTexture;
		std::shared_ptr<CTexture2D> m_pSpecularTexture;
		float m_Shininess;
		bool m_ReceiveShadow;
		static std::shared_ptr<CShader> m_Shader;
	};
}