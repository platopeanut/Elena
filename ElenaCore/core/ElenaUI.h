#pragma once

namespace Elena
{
	class CElenaUI
	{
	public:
		static void init();
		static void renderStart();
		static void renderEnd();
		static void destroy();
	private:
		CElenaUI() = delete;
		CElenaUI(const CElenaUI&) = delete;
		CElenaUI& operator=(const CElenaUI&) = delete;
	};
}