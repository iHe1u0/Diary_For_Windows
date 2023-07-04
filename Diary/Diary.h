#pragma once

#include <memory>
#include "resource.h"
#include "dialog.h"

constexpr auto MAX_LOADSTRING = 109;

// ȫ�ֱ���:
HINSTANCE handleInstance;
WCHAR appTitleString[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
auto dialog = std::make_shared<fkkt::Dialog>();
// �༭��
Widget editBox;

// �˴���ģ���а����ĺ�����ǰ������:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);