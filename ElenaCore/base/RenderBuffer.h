#pragma once

#include <glad/glad.h>

namespace Elena
{
	class CRenderBuffer
	{
	public:
		CRenderBuffer(int vWidth, int vHeight, GLenum vInternalformat);
		~CRenderBuffer();
	private:
		GLuint m_RenderBufferID;
	};
}