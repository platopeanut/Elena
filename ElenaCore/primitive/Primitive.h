#pragma once

#include <memory>
#include "base/VertexBuffer.h"

namespace Elena
{
	class CPrimitive
	{
	public:
		static const std::shared_ptr<CVertexBuffer>& createCube();
		static const std::shared_ptr<CVertexBuffer>& createPlane();
		static const std::shared_ptr<CVertexBuffer>& createQuad();
		static void clear();
	private:
		static std::shared_ptr<CVertexBuffer> m_pCube;
		static std::shared_ptr<CVertexBuffer> m_pPlane;
		static std::shared_ptr<CVertexBuffer> m_pQuad;
	};
}