#pragma once

#include <memory>
#include "resource.h"
#include "dialog.h"

constexpr auto MAX_LOADSTRING = 100;

// ȫ�ֱ���:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
auto dialog = std::make_shared<fkkt::Dialog>();

// �˴���ģ���а����ĺ�����ǰ������:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);