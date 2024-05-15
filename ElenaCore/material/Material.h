#pragma once

#include <memory>

namespace Elena
{
	class CNode;
	class CMaterial
	{
	public:
		virtual void use(const std::shared_ptr<CNode>& vNode) const = 0;
	};
}