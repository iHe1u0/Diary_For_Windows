#pragma once
#include <string>

namespace fkkt {
	class Dialog
	{
		typedef LPCWSTR String;
	public:
		void showMsg(String msg, String title = L"��ʾ")const;
	};

}