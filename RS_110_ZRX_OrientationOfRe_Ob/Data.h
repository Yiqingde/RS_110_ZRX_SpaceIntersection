/***************************************************************************
*  文件名:<Data.h>                                                         *
*                                                                          *
*  描述:储存主要元素                                                       *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年4月19日        引用              张睿祥                       *
*                                                                          *
*  外部过程：                                                              *
*                                                                          *
/**************************************************************************/
#pragma once
class CData
{
public:
	CData(void);
	~CData(void);
	//点位元素   
	double dLx;  //左片x
	double dLy;  //左片x
	double dRx;  //右片x
	double dRy;  //右片y
	double X;    //X
	double Y;    //Y
	double Z;    //Z 
	//总体元素状况 
	int iSUM;         //全部点个数
	int iKnown;       //已知点个数
	int iUnknown;     //未知点个数
};

