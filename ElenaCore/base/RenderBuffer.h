#pragma once

#include <glad/glad.h>

namespace Elena
{
	class CRenderBuffer
	{
	public:
		CRenderBuffer(int vWidth, int vHeight, GLenum vInternalformat);
		~CRenderBuffer();
		GLuint getRenderBufferID() const { return m_RenderBufferID; }
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
	private:
		GLuint m_RenderBufferID;
		int m_Width;
		int m_Height;
	};
}