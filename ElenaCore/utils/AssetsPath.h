#pragma once

#include <string>

namespace Elena
{
	class CAssetsPath
	{
	public:
		static const std::string& getRootPath();
		static std::string getAssetsPath();
		static std::string getBuiltInShaderPath(const std::string& vShaderName);
	private:
		static std::string m_RootPath;
	};
}