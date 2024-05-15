#include "FrameBuffer.h"
#include <spdlog/spdlog.h>
#include "utils/def.h"

namespace Elena
{
	CFrameBuffer::CFrameBuffer() :m_FrameBufferID{ 0 }
	{
		GL_SAFE_CALL(glGenFramebuffers(1, &m_FrameBufferID));
	}

	CFrameBuffer::~CFrameBuffer()
	{
		GL_SAFE_CALL(glDeleteFramebuffers(1, &m_FrameBufferID));
	}

	void CFrameBuffer::bind() const
	{
		GL_SAFE_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID));
	}

	void CFrameBuffer::setAttachmentTexture2D(GLenum vAttachmentType, GLuint vTextureID, GLint vTextureLevel)
	{
		GL_SAFE_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, vAttachmentType, GL_TEXTURE_2D, vTextureID, vTextureLevel));
	}

	void CFrameBuffer::setAttachmentRenderBuffer(GLenum vAttachmentType, GLuint vRenderBufferID)
	{
		GL_SAFE_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, vAttachmentType, GL_RENDERBUFFER, vRenderBufferID));
	}

	bool CFrameBuffer::check()
	{
		bool IsComplete = true;
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			IsComplete = false;
			spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		}
		return IsComplete;
	}

	void CFrameBuffer::setColorBufferEmpty()
	{
		GL_SAFE_CALL(glDrawBuffer(GL_NONE));
		GL_SAFE_CALL(glReadBuffer(GL_NONE));
	}

	void CFrameBuffer::bindDefaultFrameBuffer()
	{
		GL_SAFE_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}