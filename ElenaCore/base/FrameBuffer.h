#pragma once

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include "base/Texture2D.h"
#include "base/RenderBuffer.h"

namespace Elena
{
	class CFrameBuffer
	{
	public:
		CFrameBuffer();
		~CFrameBuffer();
		void bind() const;
		void updateViewport() const;
		void initStandard(unsigned int vWidth, unsigned int vHeight);
		void setAttachmentTexture2D(GLenum vAttachmentType, const std::shared_ptr<CTexture2D>& vTexture2D, GLint vTextureLevel = 0);
		const std::shared_ptr<CTexture2D>& getTexture2D(GLenum vAttachmentType);
		void setAttachmentRenderBuffer(GLenum vAttachmentType, const std::shared_ptr<CRenderBuffer>& vRenderBuffer);
		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		static bool check();
		static void setColorBufferEmpty();
		static void bindDefaultFrameBuffer();
	private:
		GLuint m_FrameBufferID;
		std::unordered_map<GLenum, std::shared_ptr<CTexture2D>> m_Tex2DRecords;
		int m_Width;
		int m_Height;
	};
}