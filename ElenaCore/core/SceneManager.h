#pragma once

#include <vector>
#include <memory>
#include "Scene.h"

namespace Elena
{
	class CSceneManager
	{
	public:
		static CSceneManager& getInstance();
		const std::shared_ptr<CScene>& getActiveScene() const;
		void addScene(const std::shared_ptr<CScene>& vScene);
	private:
		CSceneManager();
		CSceneManager(const CSceneManager&) = delete;
		CSceneManager& operator=(const CSceneManager&) = delete;
		std::vector<std::shared_ptr<CScene>> m_SceneList;
		int m_ActiveSceneIdx;
	};
}