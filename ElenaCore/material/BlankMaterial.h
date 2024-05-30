#pragma once

#include "Material.h"
#include "base/Shader.h"

namespace Elena
{
	class CBlankMaterial : public CMaterial
	{
	public:
		CBlankMaterial();
		// Inherited via CMaterial
		void use(const std::shared_ptr<CNode>& vNode) const override;
	private:
		static std::shared_ptr<CShader> m_pShader;
	};
}