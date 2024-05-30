#pragma once

#include <functional>
#include <imgui/imgui.h>
#include <imgui_plugins/imfilebrowser.h>

namespace Elena
{
	class CFileDialog
	{
	public:
		static CFileDialog& getInstance();
		void setTypeFilters(const std::vector<std::string>& vFilters);
		void open(std::function<void(const std::string&)> vFnCallback);
		void display();
		void dispatch();
	private:
		CFileDialog();
		CFileDialog(const CFileDialog&) = delete;
		CFileDialog& operator=(const CFileDialog&) = delete;
		ImGui::FileBrowser m_FileDialog;
		std::function<void(const std::string&)> m_FnCallback;
	};
}