// LibSqlite3.h: LibSqlite3 DLL 的主标头文件
//

#pragma once

#include "pch.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CLibSqlite3App
// 有关此类实现的信息，请参阅 LibSqlite3.cpp
//

class CLibSqlite3App : public CWinApp
{
public:
	CLibSqlite3App();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
