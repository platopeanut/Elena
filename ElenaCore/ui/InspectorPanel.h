#pragma once

#include <optional>
#include "core/Node.h"
#include "Panel.h"

namespace Elena
{
	class CInspectorPanel : public CPanel
	{
	public:
		CInspectorPanel();
		// Inherited via CPanel
		void render(float vDeltaTime) override;
	private:
		void __loadModelFormFile() const;
		void __showSceneTree(const std::shared_ptr<CNode>& vNode);
		void __showTransform();
		void __showMaterial();
		void __showLighting();
		std::optional<std::string> m_FilePath;
		std::shared_ptr<CNode> m_pCurrSelectedNode;
	};
}