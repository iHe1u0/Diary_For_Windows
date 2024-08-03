#include <vector>
#include "StringConvert.h"

String StringConvert::CString2String(const CString &source)
{
    String str;
    LPSTR  lpszStr   = 0;
    DWORD  dwMinSize = WideCharToMultiByte(CP_OEMCP, 0, source, -1, 0, 0, 0, FALSE);
    if (0 != dwMinSize)
    {
        lpszStr = new char[dwMinSize];
        WideCharToMultiByte(CP_OEMCP, 0, source, -1, lpszStr, dwMinSize, 0, FALSE);
        str = lpszStr;
        delete[] lpszStr;
    }
    return str;
}

CString StringConvert::String2CString(const String &source)
{
    size_t   size     = source.length();
    int      wCharLen = ::MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, 0, 0);
    wchar_t *buff     = new wchar_t[wCharLen + 1];
    memset(buff, 0, (static_cast<unsigned long long>(wCharLen) + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, source.c_str(), static_cast<int>(size), static_cast<LPWSTR>(buff), wCharLen);
    return buff;
}

LPWSTR StringConvert::String2LPWSTR(const String &str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, 0, 0);
    if (size > 0)
    {
        wchar_t *pwszStr = (wchar_t *)malloc((size + 1) * sizeof(wchar_t));
        MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, pwszStr, size);
        return pwszStr;
    }
    return NULL;
}
