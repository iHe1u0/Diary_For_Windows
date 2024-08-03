#pragma once

#include <string>
#include "framework.h"

using String = std::string;

class StringConvert
{

public:
    static String CString2String(const CString &source);

    static CString String2CString(const String &source);

    static LPWSTR String2LPWSTR(const String &source);
};

#define StringW(str) StringConvert::String2LPWSTR(str)