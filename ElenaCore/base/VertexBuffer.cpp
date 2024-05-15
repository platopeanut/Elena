#include "VertexBuffer.h"
#include <numeric>
#include "utils/def.h"

namespace Elena
{
	CVertexBuffer::CVertexBuffer(const std::vector<float>& vVertices, const std::vector<unsigned int>& vIndices, const std::vector<int>& vLayout, GLenum vUsage)
		:m_VAO(0), m_VBO(0), m_EBO(0), m_IndicesSize((int)vIndices.size())
	{
		GL_SAFE_CALL(glGenVertexArrays(1, &m_VAO));
		GL_SAFE_CALL(glGenBuffers(1, &m_VBO));
		GL_SAFE_CALL(glGenBuffers(1, &m_EBO));

		GL_SAFE_CALL(glBindVertexArray(m_VAO));

		GL_SAFE_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GL_SAFE_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vVertices.size(), vVertices.data(), vUsage));

		GL_SAFE_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
		GL_SAFE_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vIndices.size(), vIndices.data(), vUsage));

		unsigned int TotalCount = std::accumulate(vLayout.begin(), vLayout.end(), 0);
		unsigned int CurrAccumCount = 0;
		for (int i = 0; i < vLayout.size(); ++i)
		{
			GL_SAFE_CALL(glVertexAttribPointer(i, vLayout[i], GL_FLOAT, GL_FALSE, TotalCount * sizeof(float), (void*)(CurrAccumCount * sizeof(float))));
			GL_SAFE_CALL(glEnableVertexAttribArray(i));
			CurrAccumCount += vLayout[i];
		}

		GL_SAFE_CALL(glBindVertexArray(0));
	}

	CVertexBuffer::~CVertexBuffer()
	{
		GL_SAFE_CALL(glBindVertexArray(m_VAO));
		GL_SAFE_CALL(glDeleteVertexArrays(1, &m_VAO));
		GL_SAFE_CALL(glDeleteBuffers(1, &m_VBO));
		GL_SAFE_CALL(glDeleteBuffers(1, &m_EBO));
	}

	void CVertexBuffer::draw() const
	{
		GL_SAFE_CALL(glBindVertexArray(m_VAO));
		GL_SAFE_CALL(glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, 0));
	}
}