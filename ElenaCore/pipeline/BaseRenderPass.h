#pragma once

#include "RenderPass.h"
#include "base/Texture2D.h"

namespace Elena
{
	class CBaseRenderPass : public CRenderPass
	{
	public:
		CBaseRenderPass() = default;
		// Inherited via CRenderPass
		void render(const std::shared_ptr<CScene>& vScene) override;
	};
}