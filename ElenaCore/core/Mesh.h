#pragma once

#include <memory>
#include "base/VertexBuffer.h"
#include "material/Material.h"

namespace Elena
{
	class CMesh
	{
	public:
		CMesh(const std::shared_ptr<CVertexBuffer>& vVertexBuffer, const std::shared_ptr<CMaterial>& vMaterial);
		const std::shared_ptr<CVertexBuffer>& getVertexBuffer() const { return m_pVertexBuffer; }
		const std::shared_ptr<CMaterial>& getMaterial() const { return m_pMaterial; }
	private:
		std::shared_ptr<CVertexBuffer> m_pVertexBuffer;
		std::shared_ptr<CMaterial> m_pMaterial;
	};
}