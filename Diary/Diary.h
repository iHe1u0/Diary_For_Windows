#pragma once

#include <memory>
#include "resource.h"
#include "dialog.h"

constexpr auto MAX_LOADSTRING = 109;

// 全局变量:
HINSTANCE handleInstance;
WCHAR appTitleString[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
auto dialog = std::make_shared<fkkt::Dialog>();
// 编辑框
Widget editBox;

// 此代码模块中包含的函数的前向声明:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);