#include "Texture2D.h"
#include <spdlog/spdlog.h>
#include <stb/stb_image.h>
#include "utils/def.h"

namespace Elena
{
	CTexture2D::CTexture2D(const std::string& vTexturePath, bool vFlipY)
		:m_TextureID(0), m_Width(-1), m_Height(-1), m_NrChannels(-1) 
	{
		GL_SAFE_CALL(glGenTextures(1, &m_TextureID));
		bind();

		stbi_set_flip_vertically_on_load(vFlipY);
		unsigned char* pData = stbi_load(vTexturePath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
		if (pData)
		{
			GLenum Format;
			if (m_NrChannels == 1) Format = GL_RED;
			else if (m_NrChannels == 3) Format = GL_RGB;
			else if (m_NrChannels == 4) Format = GL_RGBA;
			else {
				Format = GL_RGB;
				spdlog::warn("Texture channels cannot support, which is {}, path is {}", m_NrChannels, vTexturePath);
			}
			GL_SAFE_CALL(glTexImage2D(GL_TEXTURE_2D, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, pData));
			GL_SAFE_CALL(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else
		{
			spdlog::error("Failed to load texture: {}", vTexturePath);
		}
		stbi_image_free(pData);
	}

	CTexture2D::CTexture2D(int vWidth, int vHeight, int vChannels, GLenum vFormat, GLenum vDataType)
		:m_TextureID(0), m_Width(vWidth), m_Height(vHeight), m_NrChannels(vChannels)
	{
		GL_SAFE_CALL(glGenTextures(1, &m_TextureID));
		bind();
		GL_SAFE_CALL(glTexImage2D(GL_TEXTURE_2D, 0, vFormat, m_Width, m_Height, 0, vFormat, vDataType, nullptr));
	}

	CTexture2D::CTexture2D(const glm::vec3& vColor)
		:m_TextureID(0), m_Width(1), m_Height(1), m_NrChannels(3)
	{
		GL_SAFE_CALL(glGenTextures(1, &m_TextureID));
		bind();
		GL_SAFE_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, &vColor[0]));
	}

	void CTexture2D::bind() const
	{
		GL_SAFE_CALL(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

	void CTexture2D::setParameters(GLenum vName, GLint vValue)
	{
		GL_SAFE_CALL(glTexParameteri(GL_TEXTURE_2D, vName, vValue));
	}

	void CTexture2D::setParameters(GLenum vName, const GLfloat* vValue)
	{
		GL_SAFE_CALL(glTexParameterfv(GL_TEXTURE_2D, vName, vValue));
	}

	void CTexture2D::generateMipmap()
	{
		GL_SAFE_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	}
}