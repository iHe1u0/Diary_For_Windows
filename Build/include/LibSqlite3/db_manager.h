#pragma once

#include "pch.h"

class __declspec(dllexport) DBManager
{
public:
    static DBManager &getInstance()
    {
        static DBManager _instance;
        return _instance;
    }

    const char *getSqlite3Version()
    {
        return "sqlite3_libversion()";
    }

private:
    DBManager() = default;

    // ���ÿ�������͸�ֵ����
    DBManager(const DBManager &)            = delete;
    DBManager &operator=(const DBManager &) = delete;
};

#define g_DBManager DBManager::getInstance()
