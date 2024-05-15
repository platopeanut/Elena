#pragma once

#include <glad/glad.h>

namespace Elena
{
	class CTexture
	{
		virtual GLuint getTextureID() const = 0;
	};
}