#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Elena
{
	class CShader
	{
	public:
		enum class EShaderType
		{
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
		};

		CShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath);
		void use() const;
		void setInt(const std::string& vName, int vValue) const;
		void setBool(const std::string& vName, bool vValue) const;
		void setFloat(const std::string& vName, float vValue) const;
		void setVec3(const std::string& vName, const glm::vec3& vValue) const;
		void setMat4(const std::string& vName, const glm::mat4& vMat) const;
	private:
		static void __dumpShaderCodeFromFile(const std::string& vShaderPath, EShaderType vShaderType, std::string& voShaderCode);
		static GLuint __compileShader(const std::string& vShaderCode, EShaderType vShaderType);
		static void __checkCompileError(GLuint vID, EShaderType vShaderType);
		static void __checkLinkError(GLuint vID);
		static std::string __getShaderTypeName(EShaderType vShaderType);
		GLuint m_ShaderID;
	};
}