
/***************************************************************************
*  文件名:<Support.h>                                                      *
*                                                                          *
*  描述:封装所有函数的类、调用矩阵CMatrix类、CData类                       *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日        创建              张睿祥                        *
*                                                                          *
*  外部过程：                                                              *
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
	int counter_01;//相对定向迭代次数
	int counter_02;//绝对定向迭代次数
	double a1;//精度
	double a2;//精度
	CData *GCP;//储存具体元素
	CData b;//储存元素概况
	double length(double x1,double y1,double x2,double y2);//长度函数
	CString * SplitString(CString str, char split, int& iSubStrs);//分割函数
	void R1(CMatrix &R,double FA,double W,double K );//R矩阵
	//相对定向
	CMatrix X;//用来储存计算出的X
	CMatrix R;//用来储存旋转元素
	//模型点
	CMatrix P;//models
	//绝对定向
	CMatrix Obs_X;
private:
	CData *read();//读取数据
	void Re_Orientation(CData *GCP);//相对定向
	void Models();//模型点
	void Ob_Orientation();//绝对定向
	void FinalResults();//最终结果转换
	void out();//输出函数
public:
	CSupport(void);
	~CSupport(void);
	void main();//主函数
};

