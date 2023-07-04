#include "displayutils.h"

namespace fkkt {
	void DisplayUtils::setWidgetSize(const Window& window)
	{
		HWND hWnd = GetForegroundWindow();  // ����ʹ���κ�����������ô��ھ��

		RECT rect;
		GetClientRect(hWnd, &rect);
		SetWindowPos(window, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}
}