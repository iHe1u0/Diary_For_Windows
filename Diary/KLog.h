#pragma once

// #include "framework.h"
#include "StringConvert.h"

namespace fkkt
{
    class KLog
    {
    public:
        static inline void out(const String &str)
        {
            OutputDebugString(StringConvert::String2CString(str));
        };

        static inline void out(const CString &cstr)
        {
            OutputDebugString(cstr);
        };
    };
} // namespace fkkt

using namespace fkkt;