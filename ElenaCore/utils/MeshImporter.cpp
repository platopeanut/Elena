#include "MeshImporter.h"
#include <vector>
#include <spdlog/spdlog.h>
#include "material/PhongMaterial.h"

namespace Elena
{
	std::shared_ptr<CTexture2D> CMeshImporter::m_pDiffuseTex{ nullptr };
	std::shared_ptr<CTexture2D> CMeshImporter::m_pSpecularTex{ nullptr };

	std::shared_ptr<CNode> CMeshImporter::import(const std::string& vModelPath, EMaterialType vMatType)
	{
		if (m_pDiffuseTex == nullptr)
		{
			m_pDiffuseTex = std::make_shared<CTexture2D>(glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (m_pSpecularTex == nullptr)
		{
			m_pSpecularTex = std::make_shared<CTexture2D>(glm::vec3(0.0f, 0.0f, 0.0f));
		}

		Assimp::Importer AiImporter;
		const aiScene* AiScene = AiImporter.ReadFile(vModelPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
		if (!AiScene || AiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !AiScene->mRootNode)
		{
			spdlog::error("ERROR::ASSIMP:: {}", AiImporter.GetErrorString());
			return nullptr;
		}
		const auto& pRootNode = __processNode(AiScene->mRootNode, AiScene, vMatType);
		spdlog::info("Loaded Model: {}", pRootNode->getName());
		return pRootNode;
	}

	std::shared_ptr<CNode> CMeshImporter::__processNode(aiNode* vAiNode, const aiScene* vAiScene, EMaterialType vMatType)
	{
		const auto& pNode = std::make_shared<CNode>();
		pNode->setName(vAiNode->mName.C_Str());
		for (unsigned int i = 0; i < vAiNode->mNumMeshes; i++)
		{
			aiMesh* pAiMesh = vAiScene->mMeshes[vAiNode->mMeshes[i]];
			pNode->addMesh(__processMesh(pAiMesh, vAiScene, vMatType));
		}
		for (unsigned int i = 0; i < vAiNode->mNumChildren; i++)
		{
			const auto& pChildNode = __processNode(vAiNode->mChildren[i], vAiScene, vMatType);
			pChildNode->setParent(pNode);
			pNode->addChild(pChildNode);
		}
		return pNode;
	}

	std::shared_ptr<CMesh> CMeshImporter::__processMesh(aiMesh* vAiMesh, const aiScene* vAiScene, EMaterialType vMatType)
	{
		std::vector<float> Vertices;
		std::vector<unsigned int> Indices;
		for (unsigned int i = 0; i < vAiMesh->mNumVertices; i++)
		{
			// positions
			Vertices.push_back(vAiMesh->mVertices[i].x);
			Vertices.push_back(vAiMesh->mVertices[i].y);
			Vertices.push_back(vAiMesh->mVertices[i].z);
			// normals
			if (vAiMesh->HasNormals())
			{
				Vertices.push_back(vAiMesh->mNormals[i].x);
				Vertices.push_back(vAiMesh->mNormals[i].y);
				Vertices.push_back(vAiMesh->mNormals[i].z);
			}
			// texture coordinates
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			if (vAiMesh->mTextureCoords[0])
			{
				Vertices.push_back(vAiMesh->mTextureCoords[0][i].x);
				Vertices.push_back(vAiMesh->mTextureCoords[0][i].y);
			}
			else
			{
				Vertices.push_back(0.0f);
				Vertices.push_back(0.0f);
			}
		}
		for (unsigned int i = 0; i < vAiMesh->mNumFaces; i++)
		{
			aiFace Face = vAiMesh->mFaces[i];
			for (unsigned int j = 0; j < Face.mNumIndices; j++)
				Indices.push_back(Face.mIndices[j]);
		}
		const auto& pVertexBuffer = std::make_shared<CVertexBuffer>(Vertices, Indices, std::vector<int>{3, 3, 2});
		if (vMatType != EMaterialType::PHONG)
			spdlog::warn("Import Material not Supported");
		return std::make_shared<CMesh>(pVertexBuffer, std::make_shared<CPhongMaterial>(m_pDiffuseTex, m_pSpecularTex, 32.0f, true));
	}
}