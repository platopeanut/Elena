#include "FrameBuffer.h"
#include <spdlog/spdlog.h>
#include "utils/def.h"

namespace Elena
{
	CFrameBuffer::CFrameBuffer() :m_FrameBufferID{ 0 }, m_Tex2DRecords{}, m_Width{ -1 }, m_Height{ -1 }
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

	void CFrameBuffer::updateViewport() const
	{
		glViewport(0, 0, m_Width, m_Height);
	}

	void CFrameBuffer::initStandard(unsigned int vWidth, unsigned int vHeight)
	{
		bind();
		const auto& pColorBuffer = std::make_shared<CTexture2D>(vWidth, vHeight, 3, GL_RGB, GL_UNSIGNED_BYTE);
		CTexture2D::setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		CTexture2D::setParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		setAttachmentTexture2D(GL_COLOR_ATTACHMENT0, pColorBuffer);
		//const auto& pDepthStencilBuffer = std::make_shared<CRenderBuffer>(vWidth, vHeight, GL_DEPTH24_STENCIL8);
		//setAttachmentRenderBuffer(GL_DEPTH_STENCIL_ATTACHMENT, pDepthStencilBuffer);
		const auto& pDepthStencilBuffer = std::make_shared<CTexture2D>(vWidth, vHeight, 3, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
		setAttachmentTexture2D(GL_DEPTH_ATTACHMENT, pDepthStencilBuffer);
		check();
	}

	void CFrameBuffer::setAttachmentTexture2D(GLenum vAttachmentType, const std::shared_ptr<CTexture2D>& vTexture2D, GLint vTextureLevel)
	{
		GL_SAFE_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, vAttachmentType, GL_TEXTURE_2D, vTexture2D->getTextureID(), vTextureLevel));
		m_Tex2DRecords[vAttachmentType] = vTexture2D;
		m_Width = vTexture2D->getWidth();
		m_Height = vTexture2D->getHeight();
	}

	const std::shared_ptr<CTexture2D>& CFrameBuffer::getTexture2D(GLenum vAttachmentType)
	{
		if (m_Tex2DRecords.count(vAttachmentType) == 0) return nullptr;
		return m_Tex2DRecords[vAttachmentType];
	}

	void CFrameBuffer::setAttachmentRenderBuffer(GLenum vAttachmentType, const std::shared_ptr<CRenderBuffer>& vRenderBuffer)
	{
		GL_SAFE_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, vAttachmentType, GL_RENDERBUFFER, vRenderBuffer->getRenderBufferID()));
		m_Width = vRenderBuffer->getWidth();
		m_Height = vRenderBuffer->getHeight();
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