#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"

namespace Elena
{
	class CTexture2D : public CTexture
	{
	public:
		CTexture2D(const std::string& vTexturePath, bool vFlipY = false);
		CTexture2D(int vWidth, int vHeight, int vChannels, GLenum vFormat, GLenum vDataType);
		CTexture2D(const glm::vec3& vColor);
		void bind() const;
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getChannels() const { return m_NrChannels; }
		// Inherited via CTexture
		GLuint getTextureID() const override { return m_TextureID; }
		static void setParameters(GLenum vName, GLint vValue);
		static void setParameters(GLenum vName, const GLfloat* vValue);
		static void generateMipmap();
	private:
		GLuint m_TextureID;
		int m_Width;
		int m_Height;
		int m_NrChannels;
	};
}