#include "StdAfx.h"
#include "Support.h"
#define f 0.15;

CSupport::CSupport(void)
{
}


CSupport::~CSupport(void)
{
}

/***************************************************************************
*  名字：void CSupport::R1(CMatrix &R,CMatrix X )                          *
*                                                                          *
*  描述：R矩阵赋值                                                         *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年4月20日       创建该函数          张睿祥                      *
*  参数： 1.CMatrix &R           //R矩阵 （3，3）                          *
*         2.CMatrix X            // X矩阵（6，1）                          *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::R1(CMatrix &R,double FA,double W,double K )
{
	R(0,0)=cos(FA)*cos(K)-sin(FA)*sin(W)*sin(K);
	R(0,1)=-cos(FA)*sin(K)-sin(FA)*sin(W)*cos(K);
	R(0,2)=-sin(FA)*cos(W);
	R(1,0)=cos(W)*sin(K);
	R(1,1)=cos(W)*cos(K);
	R(1,2)=-sin(W);
	R(2,0)=sin(FA)*cos(K)+cos(FA)*sin(W)*sin(K);
	R(2,1)=-sin(FA)*sin(K)+cos(FA)*sin(W)*cos(K);
	R(2,2)=cos(FA)*cos(W);
}
/***************************************************************************
*  名字：double length(double x1,double y1,double x2,double y2)            *
*                                                                          *
*  描述：由（x1,y1）和(x2,y2)计算两点之间距离 长度                         *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年3月20日       创建该函数          张睿祥                      *
*  参数： 1.double x1                                                      *
*         2.double y1                                                      *
*         3.double x2                                                      *
*         4.double y2                                                      *
*  返回值：double类型数据 返回距离                                         *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
double CSupport::length(double x1,double y1,double x2,double y2)
{
	double tmp=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return sqrt(tmp);
}

/***************************************************************************
*  名字：CString * CSupport::SplitString(CString str, char split, int& iSubStrs)*
*                                                                          *
*  描述：字符串分割函数2                                                   *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 1.CString str                                                    *
*         2.char split                                                     *
*         3.int& iSubStrs                                                  *
*  返回值：返回指针   指针带有动态数组的内容                               *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
CString * CSupport::SplitString(CString str, char split, int& iSubStrs)
{
    int iPos = 0; //分割符位置
    int iNums = 0; //分割符的总数
    CString strTemp = str;
    CString strRight;
    //先计算子字符串的数量
    while (iPos != -1)
    {
        iPos = strTemp.Find(split);
        if (iPos == -1)
        {
            break;
        }
        strRight = strTemp.Mid(iPos + 1, str.GetLength());
        strTemp = strRight;
        iNums++;
    }
    if (iNums == 0) //没有找到分割符
    {
        //子字符串数就是字符串本身
        iSubStrs = 1; 
        return NULL;
    }
    //子字符串数组
    iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1
    CString* pStrSplit;
    pStrSplit = new CString[iSubStrs];
    strTemp = str;
    CString strLeft;
    for (int i = 0; i < iNums; i++)
    {
        iPos = strTemp.Find(split);
        //左子串
        strLeft = strTemp.Left(iPos);
        //右子串
        strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
        strTemp = strRight;
        pStrSplit[i] = strLeft;
    }
    pStrSplit[iNums] = strTemp;
    return pStrSplit;
}
/***************************************************************************
*  名字：CData * CSupport::read(CString &strView)                          *
*                                                                          *
*  描述：读取函数                                                          *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 1.CString &strView                                               *
*  返回值：返回开辟动态数组的首地址 另外将提取的值赋给strView              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
CData  *CSupport::read()
{
	CFileDialog dlgFile(TRUE,_T("txt"),NULL,
	OFN_ALLOWMULTISELECT|OFN_EXPLORER,
	//_T("(文本文件)|*.txt"));
	_T(""));
	if(dlgFile.DoModal()==IDCANCEL) return NULL;
	CString strName=dlgFile.GetPathName();//获取打开文件文件名（路径）
	setlocale(LC_ALL,"");
	CStdioFile sf;
	if(! sf.Open(strName,CFile::modeRead)) return NULL;
	CString strLine;
	CString strContent;//接受内容字符串
	strContent.Empty();
	BOOL bEOF =sf.ReadString (strLine);
	if(!bEOF)
	{
		AfxMessageBox(_T("数据有误，请检查数据文件！"));
		return NULL;
	}
	int n=0;//为下文读取做铺垫
	CString *pstrData =SplitString(strLine,',',n);
	b.iKnown=_ttoi(pstrData[0]);
	b.iUnknown=_ttoi(pstrData[1]);
	b.iSUM=b.iKnown+b.iUnknown;
	delete [] pstrData;
	pstrData=NULL;
	
	GCP=new CData [b.iSUM];//创建动态数组
	int i=0;
	while (bEOF)
	{
		
		bEOF=sf.ReadString(strLine);
		CString *pstrData =SplitString(strLine,',',n);
		if(pstrData==NULL) continue;
		if(i<b.iKnown)
		{
		GCP[i].dLx=_tstof(pstrData[0])/1000;
		GCP[i].dLy=_tstof(pstrData[1])/1000;
		GCP[i].dRx=_tstof(pstrData[2])/1000;
		GCP[i].dRy=_tstof(pstrData[3])/1000;
		GCP[i].X=_tstof(pstrData[4]);
		GCP[i].Y=_tstof(pstrData[5]);
		GCP[i].Z=_tstof(pstrData[6]);
		}
		else if(i<b.iSUM)
		{
		GCP[i].dLx=_tstof(pstrData[0])/1000;
		GCP[i].dLy=_tstof(pstrData[1])/1000;
		GCP[i].dRx=_tstof(pstrData[2])/1000;
		GCP[i].dRy=_tstof(pstrData[3])/1000;
		}
		i++;
		delete [] pstrData;
	    pstrData=NULL;

	}
	sf.Close();
	return GCP;
}


/***************************************************************************
*  名字：void CSupport::Re_Orientation(CData *GCP)                         *
*                                                                          *
*  描述：相对定向 进行数据加工 得出5个元素                                 *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 1.CData *GCP  储存数组元素                                       *
*  返回值：返回指针   指针带有动态数组的内容                               *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::Re_Orientation(CData *GCP)
{
	
	//初始化
	counter_01=0;
	X.SetSize(5,1);
	R.SetSize(3,3);
	CMatrix _x(5,1),A(6,5),L(6,1);
	for (int i=0;i<5;i++)
	{
			X(i,0)=0;
	}
	double bx=GCP[0].dLx-GCP[0].dRx;
	do
	{
	R1(R,X(0,0),X(1,0),X(2,0));
	for (int i = 0; i < 6; i++)
	{
	CMatrix L_XYZ(3,1);
	CMatrix R_XYZ(3,1);
	L_XYZ(0,0)=GCP[i].dLx;//X1
	L_XYZ(1,0)=GCP[i].dLy;//Y1
	L_XYZ(2,0)=-f;        //Z1 
	R_XYZ(0,0)=GCP[i].dRx;//X2
	R_XYZ(1,0)=GCP[i].dRy;//Y2
	R_XYZ(2,0)=-f;        //Z2
	R_XYZ=R*R_XYZ;

	double by=bx*X(3,0);
	double bz=bx*X(4,0);

	double N1=(bx*R_XYZ(2,0)-bz*R_XYZ(0,0))/(L_XYZ(0,0)*R_XYZ(2,0)-R_XYZ(0,0)*L_XYZ(2,0));
	double N2=(bx*L_XYZ(2,0)-bz*L_XYZ(0,0))/(L_XYZ(0,0)*R_XYZ(2,0)-R_XYZ(0,0)*L_XYZ(2,0));

	double Q=N1*L_XYZ(1,0)-N2*R_XYZ(1,0)-by;
	
	L(i,0)=Q;
	A(i,0)=-R_XYZ(0,0)*R_XYZ(1,0)*N2/R_XYZ(2,0);
	A(i,1)=-(R_XYZ(2,0)+R_XYZ(1,0)*R_XYZ(1,0)/R_XYZ(2,0))*N2;
	A(i,2)=R_XYZ(0,0)*N2;
	A(i,3)=bx;
	A(i,4)=-R_XYZ(1,0)*bx/R_XYZ(2,0);
	}

	_x=(~A*A).Inv()*~A*L;
	X=X+_x;
	counter_01++;
	double mmm[5];
	mmm[0]=_x(0,0);
	mmm[1]=_x(1,0);
	mmm[2]=_x(2,0);
	mmm[3]=_x(3,0);
	mmm[4]=_x(4,0);
	}
	while(fabs(_x(0, 0))>0.00003||fabs(_x(1, 0))>0.00003||fabs(_x(2, 0))>0.00003||fabs(_x(3, 0))>0.00003||fabs(_x(4, 0))>0.00003);

	CMatrix V;
	
	V=A*_x-L;
	a1=sqrt((~V*V)(0, 0)/6);
}

/***************************************************************************
*  名字：void CSupport::Models()                                           *
*                                                                          *
*  描述：模型点计算   计算每个点的值，并将其储存至P中                      *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 无                                                               *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::Models()
{
	P.SetSize(9,3);

	double L_m=length(GCP[0].dLx,GCP[0].dLy,GCP[1].dLx,GCP[1].dLy);
	double R_m=length(GCP[0].dRx,GCP[0].dRy,GCP[1].dRx,GCP[1].dRy);
	//double m=L_m/R_m;
	double m=10000;
	R1(R,X(0,0),X(1,0),X(2,0));
	CMatrix L_XYZ(3,1);
	CMatrix R_XYZ(3,1);
	for (int i = 0; i < 9; i++)
	{
	L_XYZ(0,0)=GCP[i].dLx;//X1
	L_XYZ(1,0)=GCP[i].dLy;//Y1
	L_XYZ(2,0)=-f;        //Z1 
	R_XYZ(0,0)=GCP[i].dRx;//X2
	R_XYZ(1,0)=GCP[i].dRy;//Y2
	R_XYZ(2,0)=-f;        //Z2
	R_XYZ=R*R_XYZ;

	double bx=GCP[0].dLx-GCP[0].dRx;
	double by=bx*X(3,0);
	double bz=bx*X(4,0);

	double N1=(bx*R_XYZ(2,0)-bz*R_XYZ(0,0))/(L_XYZ(0,0)*R_XYZ(2,0)-R_XYZ(0,0)*L_XYZ(2,0));
	double N2=(bx*L_XYZ(2,0)-bz*L_XYZ(0,0))/(L_XYZ(0,0)*R_XYZ(2,0)-R_XYZ(0,0)*L_XYZ(2,0));


	double df=0.15;
	double xp = m*N1*L_XYZ(0,0);
    double yp = 0.5*m*(N1*L_XYZ(1,0)+N2*R_XYZ(1, 0)+by);
	double tmp = L_XYZ(2,0);
    double zp = df*m*(1-N1);
	

	P(i,0)=xp;
    P(i,1)=yp;
	P(i,2)=zp;
	}
}

/***************************************************************************
*  名字：void CSupport::Ob_Orientation()                                   *
*                                                                          *
*  描述：绝对定向                                                          *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 无                                                               *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::Ob_Orientation()
{
	counter_02=0;
	Obs_X.SetSize(7,1);
	for (int i=0;i<7;i++)
	{
		Obs_X(i,0)=0;
	}
	Obs_X(3,0)=1;//表示 人

	CMatrix Obs_A(12, 7),Obs_L(12, 1),Obs_V(12, 1),Obs_R(3,3),Obs__x(7,1);
	do
	{
		
		for(int i=0;i<4;i++)
		{
		R1(Obs_R,Obs_X(4,0),Obs_X(5,0),Obs_X(6,0));
		
		//对A矩阵赋值
		double _XP=P(i,0);
		double _YP=P(i,1);
		double _ZP=P(i,2);
		Obs_A(3*i,0)=1;
		Obs_A(3*i,1)=0;
		Obs_A(3*i,2)=0;
		Obs_A(3*i,3)=_XP;
		Obs_A(3*i,4)=-_ZP;
		Obs_A(3*i,5)=0;
		Obs_A(3*i,6)=-_YP;

		Obs_A(3*i+1,0)=0;
		Obs_A(3*i+1,1)=1;
		Obs_A(3*i+1,2)=0;
		Obs_A(3*i+1,3)=_YP;
		Obs_A(3*i+1,4)=0;
		Obs_A(3*i+1,5)=-_ZP;
		Obs_A(3*i+1,6)=_XP;

		Obs_A(3*i+2,0)=0;
		Obs_A(3*i+2,1)=0;
		Obs_A(3*i+2,2)=1;
		Obs_A(3*i+2,3)=_ZP;
		Obs_A(3*i+2,4)=_XP;
		Obs_A(3*i+2,5)=_YP;
		Obs_A(3*i+2,6)=0;


		//对Obs_L(12, 1)赋值
		CMatrix XYZ_TP(3,1);
		CMatrix XYZ_P(3,1);
		CMatrix temp_P(3,1);
		CMatrix temp_L(3,1);
		
        XYZ_TP(0,0)=GCP[i].X;
        XYZ_TP(1,0)=GCP[i].Y;
		XYZ_TP(2,0)=GCP[i].Z;

        XYZ_P(0,0)=P(i,0);//P未重心化
		XYZ_P(1,0)=P(i,1);
		XYZ_P(2,0)=P(i,2);

		temp_P(0,0)=Obs_X(0,0);
		temp_P(1,0)=Obs_X(1,0);
		temp_P(2,0)=Obs_X(2,0);

		temp_L=XYZ_TP-Obs_X(3,0)*Obs_R*XYZ_P-temp_P;//  要求Xp重心化 这里的XP即XYZ_P未重心化   XTp也未重心化 XYZ_TP
		

		Obs_L(3*i, 0)=temp_L(0,0);
        Obs_L(3*i+1, 0)=temp_L(1,0);
		Obs_L(3*i+2, 0)=temp_L(2,0);
		}

		Obs__x=(~Obs_A*Obs_A).Inv()*~Obs_A*Obs_L;
		Obs_X=Obs_X+Obs__x;
	    counter_02++;
	}while(fabs(Obs__x(0, 0))>0.001||fabs(Obs__x(1, 0))>0.001||fabs(Obs__x(2, 0))>0.001||fabs(Obs__x(3, 0))>0.001||fabs(Obs__x(4, 0))>0.001||fabs(Obs__x(5, 0))>0.001||fabs(Obs__x(6, 0))>0.001);

	CMatrix V;
	
	V=Obs_A*Obs__x-Obs_L;
	a2=sqrt((~V*V)(0, 0)/4);
}

/***************************************************************************
*  名字：void CSupport::FinalResults()                                     *
*                                                                          *
*  描述：进行坐标的最后转化，得以输出                                      *
*   要求Xp重心化 这里的XP即XYZ_P未重心化   XTp也未重心化 XYZ_TP            *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 无                                                               *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::FinalResults()
{
	for(int i=b.iKnown;i<b.iSUM;i++)
	{
		CMatrix temp_P(3,1);
		CMatrix temp_dX(3,1);
		temp_P(0,0)=P(i,0); 
		temp_P(1,0)=P(i,1); 
		temp_P(2,0)=P(i,2); 
		temp_dX(0,0)=Obs_X(0,0);
		temp_dX(1,0)=Obs_X(1,0);
		temp_dX(2,0)=Obs_X(2,0);
		CMatrix temp_final;
		CMatrix final_R(3,3);
		R1(final_R,Obs_X(4,0),Obs_X(5,0),Obs_X(6,0));
		temp_final=Obs_X(3,0)*final_R*temp_P+temp_dX;
		GCP[i].X=temp_final(0,0);
		GCP[i].Y=temp_final(1,0);
		GCP[i].Z=temp_final(2,0);
	}
}

/***************************************************************************
*  名字：void CSupport::out()                                              *
*                                                                          *
*  描述：输出函数                                                          *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 无                                                               *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::out()
{
	CString strOut;
	CString Result1;
	//相对定向
	for(int i=0;i<5;i++)
	{	
		Result1.Format(_T("%f\r\n"),X(i,0));
		strOut+=Result1;
	}
	Result1.Format(_T("%s%.9f%s\r\n"),
			_T("---------   相对定向精度："),
			a1,
			_T("")
			);
	strOut+=Result1;
	Result1.Format(_T("%s%d\r\n"),
			_T("---------   迭代次数："),
			counter_01
			);
	strOut+=Result1;
	Result1.Format(_T("%s\r\n"),
			_T("---------------------------------------------------------------")
			);
	strOut+=Result1;
	//模型点坐标
	Result1.Format(_T("%s\r\n"),
			_T("---------   模型点坐标：")
			);
	strOut+=Result1;
	for(int i=0;i<9;i++)
	{	
		Result1.Format(_T("%f,%f,%f\r\n"),P(i,0),P(i,1),P(i,2));
		strOut+=Result1;
	}
	Result1.Format(_T("%s\r\n"),
			_T("---------------------------------------------------------------")
			);
	strOut+=Result1;
	//绝对定向
	Result1.Format(_T("%s%s\r\n"),
			_T("---------   绝对定向"),
			_T("参数： x   y   z  l  f  w  k ")
			);
	strOut+=Result1;
	for(int i=0;i<7;i++)
	{	
		Result1.Format(_T("%f\r\n"),Obs_X(i,0));
		strOut+=Result1;
	}
	Result1.Format(_T("%s%.9f%s\r\n"),
			_T("---------   绝对定向精度："),
			a2,
			_T("")
			);
	strOut+=Result1;
	Result1.Format(_T("%s%d%s\r\n"),
			_T("---------   迭代次数："),
			counter_02,
			_T("")
			);
	strOut+=Result1;
	Result1.Format(_T("%s\r\n"),
			_T("---------------------------------------------------------------")
			);
	strOut+=Result1;
	Result1.Format(_T("%s\r\n"),
			_T("---------------------------------------------------------------")
			);
	strOut+=Result1;
	
	//最终结果
	Result1.Format(_T("%s\r\n%s\r\n"),
		_T("---------   全部元素:"),
		_T("左片x     左片y      右片x      右片y              X                                  Y                                Z    ")
		);
	strOut+=Result1;
	for(int i=0;i<9;i++)
	{
		Result1.Format(_T("%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t\r\n"),GCP[i].dLx*1000,GCP[i].dLy*1000,GCP[i].dRx*1000,GCP[i].dRy*1000,GCP[i].X,GCP[i].Y,GCP[i].Z);
		strOut+=Result1;
	}

	CStdioFile SF;
	CString strLine;
	setlocale(LC_ALL,""); 
	if(!SF.Open(_T("Result.txt"), CFile::modeCreate|CFile::modeWrite)) return;
	strLine.Format(_T("%s\r\n%s\r\n"),
			_T("---------摄影测量 相对定向--绝对定向 实验-------------------"),
			_T("---------相对定向参数    f  w  k   u  v  ")
			);
	SF.WriteString(strLine);

	SF.WriteString(strOut);
	SF.Close();
	AfxMessageBox(_T("成功!已输入至“Result.txt”中"));
}

/***************************************************************************
*  名字：void CSupport::main()                                             *
*                                                                          *
*  描述：主函数 调用函数k.read()、Re_Orientation()、FinalResults()、out()  *
*                                                                          *
*  历史：**日期**         **理由**            **签名**                     *
*      2019年5月6日       创建该函数          张睿祥                       *
*  参数： 无                                                               *
*  返回值：无                                                              *
*                                                                          *
*  注：                                                                    *
/**************************************************************************/
void CSupport::main()
{
	CSupport k;
	k.Re_Orientation(k.read());
	k.Models();
	k.Ob_Orientation();
	k.FinalResults();
	k.out();
}