#pragma once

#include "framework.h"

namespace fkkt
{
    class Dialog
    {
        // typedef LPCWSTR String;

    public:
        static void showMsg(const String &msg, const String &title = "ÌבÊ¾");
    };

} // namespace fkkt

using namespace fkkt;

#define g_Dialog Dialog

