#pragma once
#include "framework.h"


namespace fkkt {
	class DisplayUtils
	{
	public:
		static void updateWidgetSize(const Window& window);

		/**
		 * @brief 设置字体,参数解析见：
		 * https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-createfontw
		 */
		static LRESULT SetFont(const Widget& cWidget,
			const int cHeight = 18,
			const int cWidth = 0,
			const LPCWSTR fontName = L"Times New Roman",
			const int cEscapement = 0,
			const int cOrientation = 0,
			const int cWeight = FW_NORMAL,
			const DWORD bItalic = false,
			const DWORD bUnderline = false,
			const DWORD bStrikeOut = false);
	};
}

