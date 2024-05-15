#include "Node.h"

namespace Elena
{
	CNode::CNode(const std::string& vNodeName)
		:m_MeshList{}, m_pParentNode{ nullptr }, m_ChildNodes{}, m_Transform{}, m_Name{vNodeName} {}
	
	void CNode::addChild(const std::shared_ptr<CNode>& vNode)
	{
		m_ChildNodes.push_back(vNode);
	}

	void CNode::addMesh(const std::shared_ptr<CMesh>& vMesh)
	{
		m_MeshList.push_back(vMesh);
	}

	glm::mat4 CNode::getModelMatrix() const
	{
		if (m_pParentNode == nullptr) return m_Transform.getModelMatrix();
		return m_Transform.getModelMatrix() * m_pParentNode->getModelMatrix();
	}
}