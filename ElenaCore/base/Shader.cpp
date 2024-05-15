#include "Shader.h"
#include <fstream>
#include <sstream>
#include <spdlog/spdlog.h>
#include "utils/def.h"

namespace Elena
{
	CShader::CShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
	{
		std::string VertCode;
		std::string FragCode;
		__dumpShaderCodeFromFile(vVertShaderPath, EShaderType::VERTEX, VertCode);
		__dumpShaderCodeFromFile(vFragShaderPath, EShaderType::FRAGMENT, FragCode);
		GLuint VertID = __compileShader(VertCode, EShaderType::VERTEX);
		GLuint FragID = __compileShader(FragCode, EShaderType::FRAGMENT);

		m_ShaderID = glCreateProgram();
		glAttachShader(m_ShaderID, VertID);
		glAttachShader(m_ShaderID, FragID);
		glLinkProgram(m_ShaderID);
		__checkLinkError(m_ShaderID);
		glDeleteShader(VertID);
		glDeleteShader(FragID);
	}

	void CShader::use() const
	{
		GL_SAFE_CALL(glUseProgram(m_ShaderID));
	}

	void CShader::setInt(const std::string& vName, int vValue) const
	{
		GL_SAFE_CALL(glUniform1i(glGetUniformLocation(m_ShaderID, vName.c_str()), vValue));
	}

	void CShader::setBool(const std::string& vName, bool vValue) const
	{
		GL_SAFE_CALL(glUniform1i(glGetUniformLocation(m_ShaderID, vName.c_str()), (int)vValue));
	}

	void CShader::setFloat(const std::string& vName, float vValue) const
	{
		GL_SAFE_CALL(glUniform1f(glGetUniformLocation(m_ShaderID, vName.c_str()), vValue));
	}

	void CShader::setVec3(const std::string& vName, const glm::vec3& vValue) const
	{
		GL_SAFE_CALL(glUniform3fv(glGetUniformLocation(m_ShaderID, vName.c_str()), 1, &vValue[0]));
	}

	void CShader::setMat4(const std::string& vName, const glm::mat4& vMat) const
	{
		GL_SAFE_CALL(glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, vName.c_str()), 1, GL_FALSE, &vMat[0][0]));
	}

	void CShader::__dumpShaderCodeFromFile(const std::string& vShaderPath, EShaderType vShaderType, std::string& voShaderCode)
	{
		std::ifstream ShaderFile;
		ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			ShaderFile.open(vShaderPath);
			std::stringstream ShaderStream;
			ShaderStream << ShaderFile.rdbuf();
			ShaderFile.close();
			voShaderCode = ShaderStream.str();
		}
		catch (std::ifstream::failure& Error)
		{
			spdlog::error("{} shader file READ failed: {}\n{}", __getShaderTypeName(vShaderType), vShaderPath, Error.what());
		}
	}

	GLuint CShader::__compileShader(const std::string& vShaderCode, EShaderType vShaderType)
	{
		GLuint ShaderID = glCreateShader(static_cast<GLenum>(vShaderType));
		const char* ShaderCodeCStr = vShaderCode.c_str();
		glShaderSource(ShaderID, 1, &ShaderCodeCStr, nullptr);
		glCompileShader(ShaderID);
		__checkCompileError(ShaderID, vShaderType);
		return ShaderID;
	}

	void CShader::__checkCompileError(GLuint vID, EShaderType vShaderType)
	{
		GLint IsSuccess;
		GLchar InfoLog[1024];
		glGetShaderiv(vID, GL_COMPILE_STATUS, &IsSuccess);
		if (!IsSuccess)
		{
			glGetShaderInfoLog(vID, 1024, nullptr, InfoLog);
			spdlog::error("shader COMPILE failed: {}\n{}", __getShaderTypeName(vShaderType), InfoLog);
		}
		
	}

	void CShader::__checkLinkError(GLuint vID)
	{
		GLint IsSuccess;
		GLchar InfoLog[1024];
		glGetProgramiv(vID, GL_LINK_STATUS, &IsSuccess);
		if (!IsSuccess)
		{
			glGetProgramInfoLog(vID, 1024, nullptr, InfoLog);
			spdlog::error("shader LINK failed: {}", InfoLog);
		}
	}

	std::string CShader::__getShaderTypeName(EShaderType vShaderType)
	{
		if (vShaderType == EShaderType::VERTEX) return "VERTEX";
		if (vShaderType == EShaderType::FRAGMENT) return "FRAGMENT";
		if (vShaderType == EShaderType::GEOMETRY) return "GEOMETRY";
	}
}