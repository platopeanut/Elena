#include "Scene.h"

namespace Elena
{
	CScene::CScene() :m_pRootNode{ nullptr }, m_CameraList{}, m_CameraControllerList{}, m_ActiveCameraIdx{ -1 }, m_LightList{} {}

	const std::shared_ptr<CCamera>& CScene::getActiveCamera() const
	{
		if (m_ActiveCameraIdx >= 0 && m_ActiveCameraIdx < m_CameraList.size())
			return m_CameraList[m_ActiveCameraIdx];
		return nullptr;
	}

	const std::shared_ptr<CCameraController>& CScene::getActiveCameraController() const
	{
		if (m_ActiveCameraIdx >= 0 && m_ActiveCameraIdx < m_CameraList.size())
			return m_CameraControllerList[m_ActiveCameraIdx];
		return nullptr;
	}

	void CScene::addCamera(const std::shared_ptr<CCamera>& vCamera, const std::shared_ptr<CCameraController>& vCameraController)
	{
		m_CameraList.push_back(vCamera);
		m_CameraControllerList.push_back(vCameraController);
		m_ActiveCameraIdx = (int)m_CameraList.size() - 1;
	}

	void CScene::addLight(const std::shared_ptr<CLight>& vLight)
	{
		m_LightList.push_back(vLight);
	}
}