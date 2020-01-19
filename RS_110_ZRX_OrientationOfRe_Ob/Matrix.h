/***************************************************************************
*  �ļ���:<CMatrix.h>                                                      *
*                                                                          *
*  ����:������                                                             *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��5��6��        ����              �����                       *
*                                                                          *
*  �ⲿ���̣�                                                              *
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
	double **dMatData;//�������Ԫ�����ݵĶ�ά����
	int iRow;//�������
	int iCol;//�������
    
public:
	int Row() const {return iRow;}//������
	int Col() const {return iCol;}//������
    void SetSize (int row, int col);//��������Ĵ�С��ԭ�����ݲ��䣨δ���ԣ�

	double& operator () (int row, int col);//��ȡ����Ԫ��
    double  operator () (int row, int col) const;//���ػ�ȡ����Ԫ�غ�����ֻ��const�����ܷ���
	CMatrix& operator = (const CMatrix& m) ;
    
    //ע�⣺��Ԫ�������������Լ��ĳ�Ա����
    friend CMatrix operator + (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator - (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator * (const CMatrix& m1,const CMatrix& m2);
	friend CMatrix operator * (const double& num, const CMatrix& m1);
	friend CMatrix operator * (const CMatrix& m1,const double& num);

	friend CMatrix operator ~ (const CMatrix& m);//����ת��
	CMatrix Inv();//��������
	void Unit();//���ɵ�λ����
	void Allones();//����ȫһ����
	void Look();
};
