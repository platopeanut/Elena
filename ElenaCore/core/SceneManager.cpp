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
		if (m_ActiveSceneIdx >= 0 && m_ActiveSceneIdx < m_SceneList.size())
			return m_SceneList[m_ActiveSceneIdx];
		return nullptr;
	}

	CSceneManager::CSceneManager() :m_SceneList{}, m_ActiveSceneIdx{ -1 }
	{
		addScene(std::make_shared<CScene>());
	}

	void CSceneManager::addScene(const std::shared_ptr<CScene>& vScene)
	{
		m_SceneList.push_back(vScene);
		m_ActiveSceneIdx = (int)m_SceneList.size() - 1;
	}
}