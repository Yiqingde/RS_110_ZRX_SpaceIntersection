
/***************************************************************************
*  �ļ���:<Support.h>                                                      *
*                                                                          *
*  ����:��װ���к������ࡢ���þ���CMatrix�ࡢCData��                       *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��5��6��        ����              �����                        *
*                                                                          *
*  �ⲿ���̣�                                                              *
*                                                                          *
/**************************************************************************/
#pragma once
#include "Data.h"
#include "math.h"
#include "Matrix.h"
#include <locale.h>
class CSupport
{
private:
	int counter_01;//��Զ����������
	int counter_02;//���Զ����������
	double a1;//����
	double a2;//����
	CData *GCP;//�������Ԫ��
	CData b;//����Ԫ�ظſ�
	double length(double x1,double y1,double x2,double y2);//���Ⱥ���
	CString * SplitString(CString str, char split, int& iSubStrs);//�ָ��
	void R1(CMatrix &R,double FA,double W,double K );//R����
	//��Զ���
	CMatrix X;//��������������X
	CMatrix R;//����������תԪ��
	//ģ�͵�
	CMatrix P;//models
	//���Զ���
	CMatrix Obs_X;
private:
	CData *read();//��ȡ����
	void Re_Orientation(CData *GCP);//��Զ���
	void Models();//ģ�͵�
	void Ob_Orientation();//���Զ���
	void FinalResults();//���ս��ת��
	void out();//�������
public:
	CSupport(void);
	~CSupport(void);
	void main();//������
};

