// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#pragma comment(lib, "LibSqlite3.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

#include <CommCtrl.h>

// C 运行时头文件
#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
// 一些常用的 C++ 头文件
#include <string>
#include <cmath>
#include <ctime>
//

#include "utils.h"
#include <LibSqlite3/db_manager.h>

#ifndef K_DLL_EXPORT
#ifdef _K_DLL_
#define K_DLL_EXPORT __declspec(dllexport)
#else
#define K_DLL_EXPORT __declspec(dllimport)
#endif
#endif // !K_DLL_EXPORT