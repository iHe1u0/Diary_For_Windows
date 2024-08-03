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

        // ȫ�ֱ���:
        HINSTANCE listPageInstance;
        WCHAR     listTitleString[MAX_LOADSTRING];
        WCHAR     listWindowClass[MAX_LOADSTRING];
        auto      listDialog = std::make_shared<fkkt::Dialog>();
        // �б�
        Widget listView;

        ATOM             RegisterClass(HINSTANCE);
        BOOL             InitWindow(HINSTANCE, int);
        LRESULT CALLBACK ListWndProc(HWND, UINT, WPARAM, LPARAM);
        void             InitListAboutDialog(Window &window);
        INT_PTR CALLBACK ShowListAbout(HWND, UINT, WPARAM, LPARAM);
        void             onListItemClicked(const HWND &hWnd, const LPARAM &lParam);
    } // namespace listpage
} // namespace fkkt