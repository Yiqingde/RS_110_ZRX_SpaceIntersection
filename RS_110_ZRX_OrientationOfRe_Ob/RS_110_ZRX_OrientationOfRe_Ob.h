
// RS_110_ZRX_OrientationOfRe_Ob.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRS_110_ZRX_OrientationOfRe_ObApp:
// �йش����ʵ�֣������ RS_110_ZRX_OrientationOfRe_Ob.cpp
//

class CRS_110_ZRX_OrientationOfRe_ObApp : public CWinApp
{
public:
	CRS_110_ZRX_OrientationOfRe_ObApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRS_110_ZRX_OrientationOfRe_ObApp theApp;