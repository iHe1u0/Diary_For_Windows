#include "dialog.h"
#include "StringConvert.h"

void Dialog::showMsg(const String &msg, const String &title)
{
    MessageBox(NULL, StringConvert::String2CString(msg), StringConvert::String2CString(title), MB_OK);
}