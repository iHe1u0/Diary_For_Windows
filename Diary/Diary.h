#pragma once

#include <memory>
#include "dialog.h"
#include "framework.h"
#include "resource.h"

constexpr auto MAX_LOADSTRING = 109;

// 全局变量:
HINSTANCE handleInstance;
WCHAR appTitleString[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
auto dialog = std::make_shared<fkkt::Dialog>();
// 编辑框
Widget editBox;

ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

/**
 * @brief 设置字体,参数解析见：
 * https://learn.microsoft.com/zh-cn/windows/win32/api/wingdi/nf-wingdi-createfontw
 */
LRESULT SetFont(const Widget& cWidget,
	const int cHeight = 18,
	const int cWidth = 0,
	const LPCWSTR fontName = L"Times New Roman",
	const int cEscapement = 0,
	const int cOrientation = 0,
	const int cWeight = FW_NORMAL,
	const DWORD bItalic = false,
	const DWORD bUnderline = false,
	const DWORD bStrikeOut = false);