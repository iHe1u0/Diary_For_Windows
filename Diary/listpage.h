#pragma once

#include <memory>
#include "dialog.h"
#include "framework.h"
#include "resource.h"

namespace fkkt
{
    namespace listpage
    {
        constexpr auto MAX_LOADSTRING = 109;

        // 全局变量:
        HINSTANCE listPageInstance;
        WCHAR     listTitleString[MAX_LOADSTRING];
        WCHAR     listWindowClass[MAX_LOADSTRING];
        auto      listDialog = std::make_shared<fkkt::Dialog>();
        // 列表
        Widget listView;

        ATOM             RegisterClass(HINSTANCE);
        BOOL             InitWindow(HINSTANCE, int);
        LRESULT CALLBACK ListWndProc(HWND, UINT, WPARAM, LPARAM);
        void             InitListAboutDialog(Window &window);
        INT_PTR CALLBACK ShowListAbout(HWND, UINT, WPARAM, LPARAM);
        void             onListItemClicked(const HWND &hWnd, const LPARAM &lParam);
    } // namespace listpage
} // namespace fkkt