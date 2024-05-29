#include "RenderBuffer.h"
#include "utils/def.h"

namespace Elena
{
	CRenderBuffer::CRenderBuffer(int vWidth, int vHeight, GLenum vInternalformat)
		:m_RenderBufferID{ 0 }, m_Width(vWidth), m_Height(vHeight)
	{
		GL_SAFE_CALL(glGenRenderbuffers(1, &m_RenderBufferID));
		GL_SAFE_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID));
		GL_SAFE_CALL(glRenderbufferStorage(GL_RENDERBUFFER, vInternalformat, vWidth, vHeight));
	}

	CRenderBuffer::~CRenderBuffer()
	{
		GL_SAFE_CALL(glDeleteRenderbuffers(1, &m_RenderBufferID));
	}
}