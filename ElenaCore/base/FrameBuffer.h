#pragma once

#include <glad/glad.h>

namespace Elena
{
	class CFrameBuffer
	{
	public:
		CFrameBuffer();
		~CFrameBuffer();
		void bind() const;
		static void setAttachmentTexture2D(GLenum vAttachmentType, GLuint vTextureID, GLint vTextureLevel = 0);
		static void setAttachmentRenderBuffer(GLenum vAttachmentType, GLuint vRenderBufferID);
		static bool check();
		static void setColorBufferEmpty();
		static void bindDefaultFrameBuffer();
	private:
		GLuint m_FrameBufferID;
	};
}