#include "displayutils.h"

namespace fkkt {
	void DisplayUtils::updateWidgetSize(const Window& window)
	{
		HWND hWnd = GetForegroundWindow();

		RECT rect;
		GetClientRect(hWnd, &rect);
		SetWindowPos(window, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	}
	LRESULT DisplayUtils::SetFont(const Widget& cWidget, const int cHeight, const int cWidth, const LPCWSTR fontName, const int cEscapement, const int cOrientation, const int cWeight, const DWORD bItalic, const DWORD bUnderline, const DWORD bStrikeOut)
	{
		HFONT font = CreateFont(
			cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			fontName);
		if (!font)
		{
			return 1;
		}
		SendMessage(cWidget, WM_SETFONT, reinterpret_cast<WPARAM>(font), true);
		return 0;
	}
}