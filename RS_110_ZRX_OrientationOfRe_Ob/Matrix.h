/***************************************************************************
*  文件名:<CMatrix.h>                                                      *
*                                                                          *
*  描述:矩阵类                                                             *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日        引用              张睿祥                       *
*                                                                          *
*  外部过程：                                                              *
*                                                                          *
/**************************************************************************/


#pragma once
class CMatrix
{
public:
	CMatrix(int row=3,int col=3);
	// copy constructor

    CMatrix (const CMatrix& m);

	~CMatrix(void);
private:
	double **dMatData;//保存矩阵元素数据的二维数组
	int iRow;//矩阵的行
	int iCol;//矩阵的列
    
public:
	int Row() const {return iRow;}//返回行
	int Col() const {return iCol;}//返回列
    void SetSize (int row, int col);//调整数组的大小，原有数据不变（未测试）

	double& operator () (int row, int col);//获取矩阵元素
    double  operator () (int row, int col) const;//重载获取矩阵元素函数，只有const对象能访问
	CMatrix& operator = (const CMatrix& m) ;
    
    //注意：友元函数并不是类自己的成员函数
    friend CMatrix operator + (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator - (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator * (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator * (const double& num, const CMatrix& m1);
	friend CMatrix operator * (const CMatrix& m1,const double& num);

	friend CMatrix operator ~ (const CMatrix& m);//矩阵转置
	CMatrix Inv();//矩阵求逆
	void Unit();//生成单位矩阵
	void Allones();//生成全一矩阵
	void Look();
};
