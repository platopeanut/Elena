#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include "base/Shader.h"
#include "base/Texture2D.h"

namespace Elena
{
	class CProperty
	{
	public:
		CProperty(const std::string& vName) :m_Name(vName) {}
		const std::string& getName() const { return m_Name; }
		void setName(const std::string& vName) { m_Name = vName; }
		virtual bool showGui() = 0;
		virtual void setUniform(const std::shared_ptr<CShader>& vShader) const = 0;
	private:
		std::string m_Name;
	};

	class CProperties
	{
	public:
		CProperties() :m_Properties{} {}
		void addProperty(const std::shared_ptr<CProperty>& vProperty) { m_Properties.push_back(vProperty); }
		void showGui() const;
		void setUniform(const std::shared_ptr<CShader>& vShader) const;
	private:
		std::vector<std::shared_ptr<CProperty>> m_Properties;
	};

	class CPropertyBool : public CProperty
	{
	public:
		CPropertyBool(const std::string& vName, bool vValue) :CProperty(vName), m_Value(vValue) {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		bool m_Value;
	};

	class CPropertyInt : public CProperty
	{
	public:
		CPropertyInt(const std::string& vName, int vValue) :CProperty(vName), m_Value(vValue) {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		int m_Value;
	};

	class CPropertyFloat : public CProperty
	{
	public:
		CPropertyFloat(const std::string& vName, float vValue) :CProperty(vName), m_Value(vValue) {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		float m_Value;
	};

	class CPropertyFloat3 : public CProperty
	{
	public:
		CPropertyFloat3(const std::string& vName, const glm::vec3& vValue)
			:CProperty(vName), m_Value(vValue), m_RawValue{ vValue[0], vValue[1], vValue[2] } {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		float m_RawValue[3];
		glm::vec3 m_Value;
	};

	class CPropertyFloat4 : public CProperty
	{
	public:
		CPropertyFloat4(const std::string& vName, const glm::vec4& vValue)
			:CProperty(vName), m_Value(vValue), m_RawValue{ vValue[0], vValue[1], vValue[2], vValue[3]} {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		float m_RawValue[4];
		glm::vec4 m_Value;
	};

	class CPropertyColor : public CProperty
	{
	public:
		CPropertyColor(const std::string& vName, const glm::vec4& vValue)
			:CProperty(vName), m_Value(vValue), m_RawValue{ vValue[0], vValue[1], vValue[2], vValue[3] } {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override { vShader->setUniform(getName(), m_Value); }
	private:
		float m_RawValue[4];
		glm::vec4 m_Value;
	};

	class CPropertyTex2D : public CProperty
	{
	public:
		CPropertyTex2D(const std::string& vName, const std::shared_ptr<CTexture2D>& vTexture2D, int vBindID)
			: CProperty(vName), m_pTexture2D(vTexture2D), m_BindID(vBindID) {}
		// Inherited via CProperty
		bool showGui() override;
		void setUniform(const std::shared_ptr<CShader>& vShader) const override
		{
			vShader->setUniform(getName(), m_BindID);
		}
		void setUpdateCallback(std::function<void(const std::shared_ptr<CTexture2D>&)> vFnCallback);
	private:
		int m_BindID;
		std::shared_ptr<CTexture2D> m_pTexture2D;
		std::function<void(const std::shared_ptr<CTexture2D>&)> m_FnCallback;
	};
}