#include "StdAfx.h"
#include "math.h"
#include "Matrix.h"
#include "Support.h"


/***************************************************************************
*  ���֣�double CSupport::SplitStringArray(CString str, char split, CStringArray& aStr)    *
*                                                                          *
*  �������ַ����ָ��                                                    *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��3��20��       ����                �����                      *
*  ������ 1.CString str                                                    *
*         2.char split                                                     *
*         3.CStringArray& aStr                                             *
*  ����ֵ��int�������� ����n                                               *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
int CSupport::SplitStringArray(CString str, char split, CStringArray& aStr)
{
	int startIdx = 0;
	int idx = str.Find(split, startIdx);
	aStr.RemoveAll();//�����

	while (-1 != idx)
	{
		CString sTmp = str.Mid(startIdx, idx - startIdx);
		aStr.Add(sTmp);
		startIdx = idx + 1;
		idx = str.Find(split, startIdx);
	}
	CString sTmp = str.Right(str.GetLength() - startIdx);
	if (! sTmp.IsEmpty())
		aStr.Add(sTmp);
	return aStr.GetSize();
}
/***************************************************************************
*  ���֣�double length(double x1,double y1,double x2,double y2)            *
*                                                                          *
*  �������ɣ�x1,y1����(x2,y2)��������֮����� ����                         *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��3��20��       �����ú���          �����                      *
*  ������ 1.double x1                                                      *
*         2.double y1                                                      *
*         3.double x2                                                      *
*         4.double y2                                                      *
*  ����ֵ��double�������� ���ؾ���                                         *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
double CSupport::length(double x1,double y1,double x2,double y2)
{
	double tmp=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return sqrt(tmp);
}


/***************************************************************************
*  ���֣�void CSupport::read(CString &strExample,CSupport *GCP)            *
*                                                                          *
*  ��������ȡ���ݣ������ݴ���GCP���ٵĶ�̬������                           *
*                   ���ú���SplitStringArray����                           *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.CString &strExample                                            *
*         2.CSupport *GCP                                                  *
*  ����ֵ����                                                              *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
void CSupport::read(CString &strExample,CSupport *GCP)
{
	//��dx dy dz
    int iLine;
	CStringArray aStrLine;
	iLine=SplitStringArray(strExample,13,aStrLine);
	if(iLine==0)
	{
		AfxMessageBox(_T("���������ݣ�"));
	}
	
	CStringArray aStrTmp;
	int n;

	n=SplitStringArray(aStrLine[0],',',aStrTmp);
	int temp1=_tstof(aStrTmp[0]);
	int temp2=_tstof(aStrTmp[1]);
	
	for(int i=0;i<temp1;i++)
	{
		n=SplitStringArray(aStrLine[i+1],',',aStrTmp);
		GCP[i].dLx=_tstof(aStrTmp[0])/1000;
		GCP[i].dLy=_tstof(aStrTmp[1])/1000;
		GCP[i].dRx=_tstof(aStrTmp[2])/1000;
		GCP[i].dRy=_tstof(aStrTmp[3])/1000;
		GCP[i].X=_tstof(aStrTmp[4]);
		GCP[i].Y=_tstof(aStrTmp[5]);
		GCP[i].Z=_tstof(aStrTmp[6]);
	}
	for(int i=temp1;i<temp2+temp1;i++)
	{
		n=SplitStringArray(aStrLine[i+1],',',aStrTmp);
		GCP[i].dLx=_tstof(aStrTmp[0])/1000;
		GCP[i].dLy=_tstof(aStrTmp[1])/1000;
		GCP[i].dRx=_tstof(aStrTmp[2])/1000;
		GCP[i].dRy=_tstof(aStrTmp[3])/1000;
	}
}


/***************************************************************************
*  ���֣�int CSupport::SpaceBack(��                                        *
*                                                                          *
*  �������󷽽��ắ��,���ú���length()��R1()��������                       *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.CSupport *GCP           //��ҪԪ��������                       *
*         2.int xx                                                         *
*         3.int yy                                                         *
*         4.CMatrix &Left          //�ⷽλ6��Ԫ��                         *
*         5.bool _L                //������ʶ                              *
*         6.double &Left_a0        //�����                                *
*         7.CMatrix &LeftPhotoes_Pre     //����                            *
*  ����ֵ��int t        //���ص�������                                     *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
int CSupport::SpaceBack(CSupport *GCP,int xx,int yy,CMatrix &Left,bool _L,double &Left_a0,CMatrix &LeftPhotoes_Pre)
{
	int temp=1;
	int t=0;
	int n=4;//����n����֪��
	double f=0.15;//���޸�
	double m;
	if(_L)
	{
	 m=(length(GCP[xx].X,GCP[xx].Y,GCP[yy].X,GCP[yy].Y)/length(GCP[xx].dLx,GCP[xx].dLy,GCP[yy].dLx,GCP[yy].dLy));
	}
	else 
	{
		m=(length(GCP[xx].X,GCP[xx].Y,GCP[yy].X,GCP[yy].Y)/length(GCP[xx].dRx,GCP[xx].dRy,GCP[yy].dRx,GCP[yy].dRy));
	}
	//m=10000;//m��ֵ
	double H=m*f;
	CMatrix A;
	A.SetSize(2*n,6);
	CMatrix X;
	X.SetSize(6,1);
	CMatrix L;
	L.SetSize(2*n,1);
	CMatrix _x;
	_x.SetSize(6,1);

	
	//����X��ֵ��ʼ��
	
	X(0,0)=(GCP[xx].X+GCP[yy].X)/2;//XS
	X(1,0)=(GCP[xx].Y+GCP[yy].Y)/2;//YS
	X(2,0)=((GCP[xx].Z+GCP[yy].Z)/2+m*f);//ZS
	/*
	X(0,0)=(GCP[1].X+GCP[2].X+GCP[3].X+GCP[4].X)/4;//XS
	X(1,0)=(GCP[1].Y+GCP[2].Y+GCP[3].Y+GCP[4].Y)/4;;//YS
	X(2,0)=((GCP[1].Z+GCP[2].Z+GCP[3].Z+GCP[4].Z)/4+m*f);//ZS*/
	for (int i=3;i<6;i++)
	{
			X(i,0)=0;
	}


	CMatrix R;
	R.SetSize(3,3);
	CMatrix Lz;
	Lz.SetSize(4,1);

	do
	{
     R1(R,X);

    for(int k=0;k<n;k++)
	{	
	Lz(k,0)=R(0,2)*(GCP[k].X-X(0,0))+R(1,2)*(GCP[k].Y-X(1,0))+R(2,2)*(GCP[k].Z-X(2,0));
	if(_L==1){
	A(2*k,0)=(R(0,0)*f+R(0,2)*GCP[k].dLx)/Lz(k,0);
	A(2*k,1)=(R(1,0)*f+R(1,2)*GCP[k].dLx)/Lz(k,0);
	A(2*k,2)=(R(2,0)*f+R(2,2)*GCP[k].dLx)/Lz(k,0);
	A(2*k,3)=GCP[k].dLy*sin(X(4,0))-(GCP[k].dLx*(GCP[k].dLx*cos(X(5,0))/f-GCP[k].dLy*sin(X(5,0)))+f*cos(X(5,0)))*cos(X(4,0));
	A(2*k,4)=-f*sin(X(5,0))-GCP[k].dLx*(GCP[k].dLx*sin(X(5,0))+GCP[k].dLy*cos(X(5,0)))/f;
	A(2*k,5)=GCP[k].dLy;
	A(2*k+1,0)=(R(0,1)*f+R(0,2)*GCP[k].dLy)/Lz(k,0);
	A(2*k+1,1)=(R(1,1)*f+R(1,2)*GCP[k].dLy)/Lz(k,0);
	A(2*k+1,2)=(R(2,1)*f+R(2,2)*GCP[k].dLy)/Lz(k,0);
	A(2*k+1,3)=-GCP[k].dLx*sin(X(4,0))-(GCP[k].dLy*(GCP[k].dLx*cos(X(5,0))/f+GCP[k].dLy*sin(X(5,0)))-f*sin(X(5,0)))*cos(X(4,0));
    A(2*k+1,4)=-f*cos(X(5,0))-GCP[k].dLy*(GCP[k].dLx*sin(X(5,0))+GCP[k].dLy*cos(X(5,0)))/f;
	A(2*k+1,5)=-GCP[k].dLx; 
	
	
	double _1=R(0,0)*(GCP[k].X-X(0,0))+R(1,0)*(GCP[k].Y-X(1,0))+R(2,0)*(GCP[k].Z-X(2,0));
	double _2=R(0,1)*(GCP[k].X-X(0,0))+R(1,1)*(GCP[k].Y-X(1,0))+R(2,1)*(GCP[k].Z-X(2,0));
	double _3=R(0,2)*(GCP[k].X-X(0,0))+R(1,2)*(GCP[k].Y-X(1,0))+R(2,2)*(GCP[k].Z-X(2,0));
	L(2*k,0)=GCP[k].dLx+(f*_1)/_3;
	L(2*k+1,0)=GCP[k].dLy+(f*_2)/_3;
	}
	else
	{
		
	A(2*k,0)=(R(0,0)*f+R(0,2)*GCP[k].dRx)/Lz(k,0);
	A(2*k,1)=(R(1,0)*f+R(1,2)*GCP[k].dRx)/Lz(k,0);
	A(2*k,2)=(R(2,0)*f+R(2,2)*GCP[k].dRx)/Lz(k,0);
	A(2*k,3)=GCP[k].dRy*sin(X(4,0))-(GCP[k].dRx*(GCP[k].dRx*cos(X(5,0))/f-GCP[k].dRy*sin(X(5,0)))+f*cos(X(5,0)))*cos(X(4,0));
	A(2*k,4)=-f*sin(X(5,0))-GCP[k].dRx*(GCP[k].dRx*sin(X(5,0))+GCP[k].dRy*cos(X(5,0)))/f;
	A(2*k,5)=GCP[k].dRy;
	A(2*k+1,0)=(R(0,1)*f+R(0,2)*GCP[k].dRy)/Lz(k,0);
	A(2*k+1,1)=(R(1,1)*f+R(1,2)*GCP[k].dRy)/Lz(k,0);
	A(2*k+1,2)=(R(2,1)*f+R(2,2)*GCP[k].dRy)/Lz(k,0);
	A(2*k+1,3)=-GCP[k].dRx*sin(X(4,0))-(GCP[k].dRy*(GCP[k].dRx*cos(X(5,0))/f+GCP[k].dRy*sin(X(5,0)))-f*sin(X(5,0)))*cos(X(4,0));
    A(2*k+1,4)=-f*cos(X(5,0))-GCP[k].dRy*(GCP[k].dRx*sin(X(5,0))+GCP[k].dRy*cos(X(5,0)))/f;
	A(2*k+1,5)=-GCP[k].dRx; 
	
	
	double _1=R(0,0)*(GCP[k].X-X(0,0))+R(1,0)*(GCP[k].Y-X(1,0))+R(2,0)*(GCP[k].Z-X(2,0));
	double _2=R(0,1)*(GCP[k].X-X(0,0))+R(1,1)*(GCP[k].Y-X(1,0))+R(2,1)*(GCP[k].Z-X(2,0));
	double _3=R(0,2)*(GCP[k].X-X(0,0))+R(1,2)*(GCP[k].Y-X(1,0))+R(2,2)*(GCP[k].Z-X(2,0));
	L(2*k,0)=GCP[k].dRx+(f*_1)/_3;
	L(2*k+1,0)=GCP[k].dRy+(f*_2)/_3;
	}
	
	}
	double Azhi[8];
	Azhi[0]=A(0,0);
	Azhi[1]=A(1,0);
	Azhi[2]=A(2,0);
	Azhi[3]=A(3,0);
	Azhi[4]=A(4,0);
	Azhi[5]=A(5,0);
	Azhi[6]=A(6,0);
	Azhi[7]=A(7,0);

	_x=(~A*A).Inv()*~A*L;
	X=X+_x;
	++t;
	double mmm[6];
	mmm[0]=_x(0,0);
	mmm[1]=_x(1,0);
	mmm[2]=_x(2,0);
	mmm[3]=_x(3,0);
	mmm[4]=_x(4,0);
	mmm[5]=_x(5,0);



	
	}while(fabs(_x(0,0))>1e-4||fabs(_x(1,0))>1e-4||fabs(-_x(2,0))>1e-4||fabs(_x(3,0))>4.481e-6||fabs(_x(4,0))>4.481e-6||fabs(_x(5,0))>4.481e-6);
	//ƽ������
	CMatrix Temp;
	Temp=~(_x)*(_x);
	double temp1;
	temp1=Temp(0,0);
	Left_a0=temp1/(2*n-6);
	Left_a0=sqrt(Left_a0);

	CMatrix Qxx;
	Qxx.SetSize(6,6);
	Qxx=(~A*A).Inv();
	for(int i=0;i<6;i++)
	{
		LeftPhotoes_Pre(i,0)=Left_a0*sqrt(Qxx(i,i));
	}
	Left=X;
	return t;
}


/***************************************************************************
*  ���֣�void CSupport::R1(CMatrix &R,CMatrix X )                          *
*                                                                          *
*  ������R����ֵ                                                         *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.CMatrix &R           //R���� ��3��3��                          *
*         2.CMatrix X            // X����6��1��                          *
*  ����ֵ����                                                              *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
void CSupport::R1(CMatrix &R,CMatrix X )
{
	R(0,0)=cos(X(3,0))*cos(X(5,0))-sin(X(3,0))*sin(X(4,0))*sin(X(5,0));
	R(0,1)=-cos(X(3,0))*sin(X(5,0))-sin(X(3,0))*sin(X(4,0))*cos(X(5,0));
	R(0,2)=-sin(X(3,0))*cos(X(4,0));
	R(1,0)=cos(X(4,0))*sin(X(5,0));
	R(1,1)=cos(X(4,0))*cos(X(5,0));
	R(1,2)=-sin(X(4,0));
	R(2,0)=sin(X(3,0))*cos(X(5,0))+cos(X(3,0))*sin(X(4,0))*sin(X(5,0));
	R(2,1)=-sin(X(3,0))*sin(X(5,0))+cos(X(3,0))*sin(X(4,0))*cos(X(5,0));
	R(2,2)=cos(X(3,0))*cos(X(4,0));
}

/***************************************************************************
*  ���֣�void CSupport::SpaceFront()                                       *
*                                                                          *
*  ������ǰ�����ắ��                                                      *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.CMatrix &Left           //��Ƭ6���ⷽλԪ��                    *
*         2.CMatrix &Right          //��Ƭ6���ⷽλԪ��                    *
*         3.CMatrix &B              //��Ӱ����3��Ԫ��                      *
*         4.CMatrix &R_Left          //��Ƭ��ת����3��3��                *
*         5.CMatrix &R_Right         //��Ƭ��ת����3��3��                *
*         6.CSupport *GCP           //��ҪԪ��                             *
*  ����ֵ����                                                              *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
void CSupport::SpaceFront(CMatrix &Left,CMatrix &Right,CMatrix &B,CMatrix &R_Left,CMatrix &R_Right,CSupport *GCP)
{
	double f=0.15;//���޸�
	int n=4;//�ӵ�������ʼΪ����ֵ
	int m=9;//5--9��Ϊ����
	B(0,0)=Right(0,0)-Left(0,0);
	B(1,0)=Right(1,0)-Left(1,0);
	B(2,0)=Right(2,0)-Left(2,0);

	R1(R_Left,Left);
	R1(R_Right,Right);
	//����һ������
	
	for(int i=n;i<m;i++)
	{
		CMatrix L_xyf;
		L_xyf.SetSize(3,1);
		L_xyf(0,0)=GCP[i].dLx;
		L_xyf(1,0)=GCP[i].dLy;
		L_xyf(2,0)=-f;

		CMatrix R_xyf;
		R_xyf.SetSize(3,1);
		R_xyf(0,0)=GCP[i].dRx;
		R_xyf(1,0)=GCP[i].dRy;
		R_xyf(2,0)=-f;

		
		CMatrix L;
		L.SetSize(3,1);
		CMatrix R;
		R.SetSize(3,1);
		L=R_Left*L_xyf;
		R=R_Right*R_xyf;

		double N1,N2;
		N1=((B(0,0)*R(2,0)-B(2,0)*R(0,0))/(L(0,0)*R(2,0)-R(0,0)*L(2,0)));
		N2=((B(0,0)*L(2,0)-B(2,0)*L(0,0))/(L(0,0)*R(2,0)-R(0,0)*L(2,0)));

		GCP[i].X=Right(0,0)+N2*R(0,0);
		GCP[i].Y=(Left(1,0)+Right(1,0)+N1*L(1,0)+N2*R(1,0))/2;
		GCP[i].Z=Right(2,0)+N2*R(2,0);
	}
}
/***************************************************************************
*  ���֣�void CSupport::out()                                              *
*                                                                          *
*  �������������                                                          *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.double Left_a0          //��Ƭ��λȨ�����                     *
*         2.double Right_a0          //��Ƭ��λȨ�����                    *
*         3.CMatrix LeftPhotoes             //��Ƭ�ⷽλԪ��               *
*         4.CMatrix LeftPhotoes_Pre          //��Ƭ�ⷽλԪ�ؾ���          *
*         5.CMatrix RightPhotoes            //��Ƭ�ⷽλԪ��               *
*         6.CMatrix RightPhotoes_Pre         //��Ƭ�ⷽλԪ�ؾ���          *
*         7.CSupport *GCP                  //��ҪԪ��                      *
*         8.CString &strResult                //������CString            *
*         9.int t1                           //��Ƭ��������                *
*         10.int t2                          //��Ƭ��������                *
*  ����ֵ����                                                              *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
void CSupport::out(double Left_a0,double Right_a0,CMatrix LeftPhotoes,CMatrix LeftPhotoes_Pre,CMatrix RightPhotoes,CMatrix RightPhotoes_Pre,CSupport *GCP ,CString &strResult,int t1,int t2)
{
		strResult.Format(_T("%s\t%s\t%s\t\r\n"),
		_T("-------------------------------------------------------- ��Ӱ�ⷽλԪ��  -------------------------------------------------------- "),
		_T(""),
		_T("")
		);
	
	CString strOutput;
	strResult=strResult+strOutput;
	strOutput.Format(_T("%s%f%s%d\r\n%s\r\n"),
		_T("��Ƭ��λȨ�����:"),
		Left_a0,
		_T("                                  ��������:"),
		t1,
		_T("��ƬԪ�أ������� Xs  Ys  Zs   Alfa   w   k:                                      ���ȣ�")
		);
	strResult=strResult+strOutput;
		for(int z=0;z<6;z++)
	{
		if(z<3)
		{
			strOutput.Format(_T("%f\t\t\t\t\t\t%f\r\n"),LeftPhotoes(z,0),LeftPhotoes_Pre(z,0));
		}
		else
		{
			strOutput.Format(_T("%f\t\t\t\t\t\t\t%f\r\n"),LeftPhotoes(z,0),LeftPhotoes_Pre(z,0));
		}
		strResult=strResult+strOutput;
	}
	strOutput.Format(_T("%s%f%s%d\r\n%s\r\n"),
		_T("��Ƭ��λȨ����"),
		Right_a0,
		_T("                                  ��������:"),
		t2,
		_T("��ƬԪ�أ������� Xs  Ys  Zs   Alfa   w   k:                                      ���ȣ�")
		);
	strResult=strResult+strOutput;
	for(int z=0;z<6;z++)
	{
		if(z<3)
		{
		strOutput.Format(_T("%f\t\t\t\t\t\t%f\r\n"),RightPhotoes(z,0),RightPhotoes_Pre(z,0));
		}
		else
		{
		strOutput.Format(_T("%f\t\t\t\t\t\t\t%f\r\n"),RightPhotoes(z,0),RightPhotoes_Pre(z,0));
		}
		strResult=strResult+strOutput;

	}
	strOutput.Format(_T("%s\r\n%s\r\n"),
		_T("ȫ��Ԫ��:"),
		_T("��Ƭx     ��Ƭy      ��Ƭx      ��Ƭy              X                       Y                     Z    ")
		);
	strResult=strResult+strOutput;	
	for(int i=0;i<9;i++)
	{
		strOutput.Format(_T("%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t\r\n"),GCP[i].dLx*1000,GCP[i].dLy*1000,GCP[i].dRx*1000,GCP[i].dRy*1000,GCP[i].X,GCP[i].Y,GCP[i].Z);
		strResult=strResult+strOutput;
	}

}


/***************************************************************************
*  ���֣�void CSupport::main(CString &strExample,CString &strResult)       *
*                                                                          *
*  ��������Ҫ���� �����ú���read()��SpqceBack()��SpaceFront()��out()�Ⱥ��� *
*                    ��4������                                             *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��20��       �����ú���          �����                      *
*  ������ 1.CString &strExample          //��������                        *
*         2.CString &strResult          //�������                         *
*  ����ֵ����                                                              *
*                                                                          *
*  ע��                                                                    *
/**************************************************************************/
void CSupport::main(CString &strExample,CString &strResult)
{
	
	CSupport GCP[9];//���޸�
	read(strExample,GCP);//��ȡ����
	
	
	CMatrix LeftPhotoes;//��Ƭ�ⷽλԪ��
	LeftPhotoes.SetSize(6,1);
	double Left_a0;//�����
	CMatrix LeftPhotoes_Pre;//��Ƭ�ⷽλԪ��
	LeftPhotoes_Pre.SetSize(6,1);

	CMatrix RightPhotoes;//��Ƭ�ⷽλԪ��
	RightPhotoes.SetSize(6,1);
	double Right_a0;//�����
	CMatrix RightPhotoes_Pre;//��Ƭ�ⷽλԪ��
	RightPhotoes_Pre.SetSize(6,1);
	
	double LeftPhotoes_t1=SpaceBack(GCP,0,2,LeftPhotoes,1,Left_a0,LeftPhotoes_Pre);//��Ƭ�󷽽���
	double RightPhotoes_t2=SpaceBack(GCP,1,3,RightPhotoes,0,Right_a0,RightPhotoes_Pre);//��Ƭ�󷽽���

	


	CMatrix B;
	B.SetSize(3,1);//Bx By Bz
	CMatrix R_Left;
	R_Left.SetSize(3,3);//��Ƭ��ת����R
	CMatrix R_Right;                                                     
	R_Right.SetSize(3,3);//��Ƭ��ת����R
	SpaceFront(LeftPhotoes,RightPhotoes,B,R_Left,R_Right,GCP);

	out(Left_a0,Right_a0,LeftPhotoes,LeftPhotoes_Pre,RightPhotoes,RightPhotoes_Pre,GCP,strResult,LeftPhotoes_t1,RightPhotoes_t2);
}

CSupport::CSupport(void)
{
}


CSupport::~CSupport(void)
{
}
