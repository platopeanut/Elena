#pragma once

#include <vector>
#include <string>
#include "Transform.h"
#include "Mesh.h"

namespace Elena
{
	class CNode
	{
	public:
		CNode(const std::string& vNodeName = "");
		void addMesh(const std::shared_ptr<CMesh>& vMesh);
		void addChild(const std::shared_ptr<CNode>& vNode);
		const std::vector<std::shared_ptr<CMesh>>& getMeshList() const { return m_MeshList; }
		const std::vector<std::shared_ptr<CNode>>& getChildNodes() const { return m_ChildNodes; }
		CTransform& getTransform() { return m_Transform; }
		glm::mat4 getModelMatrix() const;
		const std::string& getName() const { return m_Name; }
		void setName(const std::string& vName) { m_Name = vName; }
		void setParent(const std::shared_ptr<CNode>& vNode) { m_pParentNode = vNode; }
	private:
		CTransform m_Transform;
		std::vector<std::shared_ptr<CMesh>> m_MeshList;
		std::shared_ptr<CNode> m_pParentNode;
		std::vector<std::shared_ptr<CNode>> m_ChildNodes;
		std::string m_Name;
	};
}