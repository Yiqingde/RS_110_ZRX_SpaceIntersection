
// RS_110_ZRX_OrientationOfRe_Ob.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CRS_110_ZRX_OrientationOfRe_ObApp:
// 有关此类的实现，请参阅 RS_110_ZRX_OrientationOfRe_Ob.cpp
//

class CRS_110_ZRX_OrientationOfRe_ObApp : public CWinApp
{
public:
	CRS_110_ZRX_OrientationOfRe_ObApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CRS_110_ZRX_OrientationOfRe_ObApp theApp;