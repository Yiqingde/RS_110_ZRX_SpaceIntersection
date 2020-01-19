/***************************************************************************
*  �ļ���:<Support.h>                                                      *
*                                                                          *
*  ����:��װ���к������ࡢ���þ���CMatrix��                                *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��19��        ����              �����                       *
*                                                                          *
*  �ⲿ���̣�                                                              *
*                                                                          *
/**************************************************************************/

#pragma once
#include"Matrix.h"

class CSupport
{
	double dLx;
	double dLy;
	double dRx;
	double dRy;
	double X;
	double Y;
	double Z;
public:
	int SplitStringArray(CString str, char split, CStringArray& aStr);
	double length(double x1,double y1,double x2,double y2);
	CSupport(void);
	~CSupport(void);
	void R1(CMatrix &R,CMatrix X );
	void read(CString &strExample,CSupport *GCP);
	int SpaceBack(CSupport *GCP,int xx,int yy,CMatrix &Left,bool _L,double &Left_a0,CMatrix &LeftPhotoes_Pre);
	void SpaceFront(CMatrix &Left,CMatrix &Right,CMatrix &B,CMatrix &R_Left,CMatrix &R_Right,CSupport *GCP);
	void out(double Left_a0,double Right_a0,CMatrix LeftPhotoes,CMatrix LeftPhotoes_Pre,CMatrix RightPhotoes,CMatrix RightPhotoes_Pre,CSupport *GCP ,CString &strResult,int t1,int t2);
	void main(CString &strExample,CString &strResult);
};

