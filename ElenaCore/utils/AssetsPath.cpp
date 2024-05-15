#include "AssetsPath.h"
#include <spdlog/spdlog.h>

namespace Elena
{
	std::string CAssetsPath::m_RootPath{};

	const std::string& CAssetsPath::getRootPath()
	{
		if (!m_RootPath.empty()) return m_RootPath;
		char* Buf = nullptr;
		size_t Size = 0;
		if (_dupenv_s(&Buf, &Size, "ELENA_ROOT") == 0 && Buf != nullptr)
		{
			m_RootPath = Buf;
			free(Buf);
			return m_RootPath;
		}
		spdlog::error("environment variable ELENA_ROOT is not defined");
		return m_RootPath;
	}

	std::string CAssetsPath::getAssetsPath()
	{
		return getRootPath() + "assets/";
	}

	std::string CAssetsPath::getBuiltInShaderPath(const std::string& vShaderName)
	{
		return getAssetsPath() + "builtIn/shaders/" + vShaderName;
	}
}