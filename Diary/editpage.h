#pragma once

#include <memory>
#include "dialog.h"
#include "framework.h"
#include "resource.h"

namespace fkkt
{
  namespace editpage
  {
    constexpr auto MAX_LOADSTRING = 109;

    //
    HINSTANCE handleInstance;
    WCHAR     appTitleString[MAX_LOADSTRING];
    WCHAR     szWindowClass[MAX_LOADSTRING];
    auto      dialog = std::make_shared<fkkt::Dialog>();
    //
    Widget editBox;

    ATOM             MyRegisterClass(HINSTANCE);
    BOOL             InitInstance(HINSTANCE, int);
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
  } // namespace editpage
} // namespace fkkt