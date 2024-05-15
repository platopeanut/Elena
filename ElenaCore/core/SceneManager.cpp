#include "SceneManager.h"

namespace Elena
{
	CSceneManager& CSceneManager::getInstance()
	{
		static CSceneManager SceneManager;
		return SceneManager;
	}

	const std::shared_ptr<CScene>& CSceneManager::getActiveScene() const
	{
		_ASSERTE(m_ActiveSceneIdx >= 0 && m_ActiveSceneIdx < m_SceneList.size());
		return m_SceneList[m_ActiveSceneIdx];
	}

	CSceneManager::CSceneManager() :m_SceneList{}, m_ActiveSceneIdx{ -1 } {}

	void CSceneManager::addScene(const std::shared_ptr<CScene>& vScene)
	{
		m_SceneList.push_back(vScene);
		m_ActiveSceneIdx = (int)m_SceneList.size() - 1;
	}
}