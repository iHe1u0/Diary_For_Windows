#include "displayutils.h"

namespace fkkt {
	void DisplayUtils::setWidgetSize(const Window& window)
	{
		HWND hWnd = GetForegroundWindow();  // 或者使用任何其他方法获得窗口句柄

		RECT rect;
		GetClientRect(hWnd, &rect);
		SetWindowPos(window, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}
}