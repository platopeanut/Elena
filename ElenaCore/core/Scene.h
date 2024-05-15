#pragma once

#include <vector>
#include <memory>
#include "Node.h"
#include "camera/Camera.h"
#include "light/Light.h"

namespace Elena
{
	class CScene
	{
	public:
		CScene();
		const std::shared_ptr<CCamera>& getActiveCamera() const;
		const std::shared_ptr<CCameraController>& getActiveCameraController() const;
		void addCamera(const std::shared_ptr<CCamera>& vCamera, const std::shared_ptr<CCameraController>& vCameraController);
		void addLight(const std::shared_ptr<CLight>& vLight);
		const std::vector<std::shared_ptr<CLight>>& getLights() const { return m_LightList; }
		void setRootNode(const std::shared_ptr<CNode>& vNode) { m_pRootNode = vNode; }
		const std::shared_ptr<CNode>& getRootNode() const { return m_pRootNode; }
	private:
		std::shared_ptr<CNode> m_pRootNode;
		std::vector<std::shared_ptr<CCamera>> m_CameraList;
		std::vector<std::shared_ptr<CCameraController>> m_CameraControllerList;
		int m_ActiveCameraIdx;
		std::vector<std::shared_ptr<CLight>> m_LightList;
	};
}