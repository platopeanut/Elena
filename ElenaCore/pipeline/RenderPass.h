#pragma once

#include "core/Scene.h"

namespace Elena
{
	class CRenderPass
	{
	public:
		virtual void render(const std::shared_ptr<CScene>& vScene) = 0;
	};
}