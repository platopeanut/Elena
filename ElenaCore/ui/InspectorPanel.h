#pragma once

#include "Panel.h"

namespace Elena
{
	class CInspectorPanel : public CPanel
	{
	public:
		// Inherited via CPanel
		void render(float vDeltaTime) override;
	};
}