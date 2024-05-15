#include "Mesh.h"

namespace Elena
{
	CMesh::CMesh(const std::shared_ptr<CVertexBuffer>& vVertexBuffer, const std::shared_ptr<CMaterial>& vMaterial)
		:m_pVertexBuffer(vVertexBuffer), m_pMaterial(vMaterial)
	{}
}