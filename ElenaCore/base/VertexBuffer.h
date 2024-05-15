#pragma once

#include <vector>
#include <glad/glad.h>

namespace Elena
{
	class CVertexBuffer
	{
	public:
		CVertexBuffer(const std::vector<float>& vVertices, const std::vector<unsigned int>& vIndices, const std::vector<int>& vLayout, GLenum vUsage = GL_STATIC_DRAW);
		~CVertexBuffer();
		void draw() const;
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
		int m_IndicesSize;
	};
}