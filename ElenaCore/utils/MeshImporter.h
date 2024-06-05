#pragma once

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "core/Node.h"
#include "material/Material.h"

namespace Elena
{
	class CMeshImporter
	{
	public:
		enum class EMaterialType
		{
			PHONG
		};
	public:
		static std::shared_ptr<CNode> import(const std::string& vModelPath, EMaterialType vMatType);
	private:
		static std::shared_ptr<CNode> __processNode(aiNode* vAiNode, const aiScene* vAiScene, EMaterialType vMatType);
		static std::shared_ptr<CMesh> __processMesh(aiMesh* vAiMesh, const aiScene* vAiScene, EMaterialType vMatType);
		static std::shared_ptr<CTexture2D> m_pDiffuseTex;
		static std::shared_ptr<CTexture2D> m_pSpecularTex;
	};
}
