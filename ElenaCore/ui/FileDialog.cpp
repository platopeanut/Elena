#include "FileDialog.h"

namespace Elena
{
	CFileDialog& CFileDialog::getInstance()
	{
		static CFileDialog Instance;
		return Instance;
	}

	void CFileDialog::setTypeFilters(const std::vector<std::string>& vFilters)
	{
		m_FileDialog.SetTypeFilters(vFilters);
	}

	void CFileDialog::open(std::function<void(const std::string&)> vFnCallback)
	{
		m_FnCallback = vFnCallback;
		if (!m_FileDialog.IsOpened()) m_FileDialog.Open();
	}

	void CFileDialog::display()
	{
		m_FileDialog.Display();
	}

	void CFileDialog::dispatch()
	{
		if (m_FileDialog.HasSelected() && m_FnCallback != nullptr)
		{
			m_FnCallback(m_FileDialog.GetSelected().string());
			m_FileDialog.ClearSelected();
		}
	}

	CFileDialog::CFileDialog()
	{
		m_FileDialog.SetTitle("Open File");
	}
}