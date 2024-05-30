#include "InspectorPanel.h"
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>
#include <queue>
#include "core/SceneManager.h"
#include "material/CheckerMaterial.h"
#include "material/BlankMaterial.h"
#include "material/PhongMaterial.h"
#include "utils/MeshImporter.h"
#include "CommonWidgets.h"
#include "FileDialog.h"
#include <utils/AssetsPath.h>

namespace Elena
{
	CInspectorPanel::CInspectorPanel() :m_pCurrSelectedNode(nullptr)
	{
	}

	void CInspectorPanel::render(float vDeltaTime)
	{
		ImGui::Begin("Inspector");
		ImGui::SetWindowFontScale(1.5f);

		if (ImGui::CollapsingHeader("File"))
		{
			if (ImGui::Button("Open Model File"))
			{
				CFileDialog::getInstance().setTypeFilters({ ".obj", ".fbx" });
				CFileDialog::getInstance().open([&](const std::string& vFilePath) {
					m_FilePath.emplace(vFilePath);
					__loadModelFormFile();
				});
			}
			ImGui::SameLine(0, 5.0f);
			ImGui::Text(m_FilePath.has_value() ? m_FilePath.value().c_str() : "None");
		}
		if (ImGui::CollapsingHeader("Hierarchy"))
		{
			__showSceneTree(CSceneManager::getInstance().getActiveScene()->getRootNode());
		}
		__showTransform();
		__showMaterial();
		ImGui::End();
		CFileDialog::getInstance().display();
		CFileDialog::getInstance().dispatch();
	}

	void CInspectorPanel::__loadModelFormFile() const
	{
		const auto& pDefaultTex = std::make_shared<CTexture2D>(glm::vec3(1.0f, 1.0f, 1.0f));
		const auto& pFaceTex = std::make_shared<CTexture2D>(CAssetsPath::getAssetsPath() + "textures/awesomeface.png");
		const auto& pNode = CMeshImporter::import(m_FilePath.value(), std::make_shared<Elena::CPhongMaterial>(pFaceTex, pDefaultTex, 32.0f));
		CSceneManager::getInstance().getActiveScene()->getRootNode()->addChild(pNode);
	}

	void CInspectorPanel::__showSceneTree(const std::shared_ptr<CNode>& vNode)
	{
		// https://www.reddit.com/r/cpp_questions/comments/x0ypqt/imgui_tree_view_implementation/
		// https://kahwei.dev/2022/06/20/imgui-tree-node/
		if (vNode == nullptr) return;
		ImGuiTreeNodeFlags Flags = 0;
		if (vNode->getChildNodes().size() == 0)
			Flags |= ImGuiTreeNodeFlags_Leaf;
		if (m_pCurrSelectedNode == vNode)
			Flags |= ImGuiTreeNodeFlags_Selected;
		if (ImGui::TreeNodeEx(vNode->getName().c_str(), Flags))
		{
			if (ImGui::IsItemClicked())
			{
				m_pCurrSelectedNode = vNode;
			}
			for (const auto& pChildNode : vNode->getChildNodes())
			{
				__showSceneTree(pChildNode);
			}
			ImGui::TreePop();
		}
	}

	void CInspectorPanel::__showTransform()
	{
		static float Position[3];
		static float Rotation[3];
		static float Scale[3];
		if (ImGui::CollapsingHeader("Transform"))
		{
			if (m_pCurrSelectedNode == nullptr) return;
			auto& Transform = m_pCurrSelectedNode->getTransform();
			if (CCommonWidgets::showInputFloat3("Position", Position, Transform.getPosition()))
				Transform.setPosition(Position);
			if (CCommonWidgets::showInputFloat3("Rotation", Rotation, Transform.getRotation()))
				Transform.setRotation(Rotation);
			if (CCommonWidgets::showInputFloat3("Scale", Scale, Transform.getScale()))
				Transform.setScale(Scale);
		}
	}

	void CInspectorPanel::__showMaterial()
	{
		if (ImGui::CollapsingHeader("Material"))
		{
			if (m_pCurrSelectedNode == nullptr) return;
			const auto& MeshList = m_pCurrSelectedNode->getMeshList();
			for (const auto& pMesh : MeshList)
			{
				const auto& pMaterial = pMesh->getMaterial();
				pMaterial->getProperties().showGui();
			}
		}
	}
}