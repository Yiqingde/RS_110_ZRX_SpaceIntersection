
// RS_110_ZRX_SpaceIntersection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRS_110_ZRX_SpaceIntersectionApp:
// �йش����ʵ�֣������ RS_110_ZRX_SpaceIntersection.cpp
//

class CRS_110_ZRX_SpaceIntersectionApp : public CWinApp
{
public:
	CRS_110_ZRX_SpaceIntersectionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRS_110_ZRX_SpaceIntersectionApp theApp;