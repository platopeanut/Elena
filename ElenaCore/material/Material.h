#pragma once

#include <memory>
#include "ui/Property.h"

namespace Elena
{
	class CNode;
	class CMaterial
	{
	public:
		virtual void use(const std::shared_ptr<CNode>& vNode) const = 0;
		const CProperties& getProperties() const { return m_Properties; }
	protected:
		CProperties m_Properties;
	};
}