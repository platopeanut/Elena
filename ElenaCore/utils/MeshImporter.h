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
		static std::shared_ptr<CNode> import(const std::string& vModelPath, const std::shared_ptr<CMaterial>& vMaterial);
	private:
		static std::shared_ptr<CNode> __processNode(aiNode* vAiNode, const aiScene* vAiScene);
		static std::shared_ptr<CMesh> __processMesh(aiMesh* vAiMesh, const aiScene* vAiScene);
		static std::shared_ptr<CMaterial> m_CurrMaterial;
	};
}
