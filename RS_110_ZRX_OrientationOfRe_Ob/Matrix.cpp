#include "StdAfx.h"
#include "Matrix.h"
#include "math.h"

CMatrix::CMatrix(int row,int col)
{
	iRow=row;
	iCol=col;
    dMatData = new double*[row];

	for (int i=0; i < row; i++)
	{
		dMatData[i]= new double[col];
		for(int j=0;j<col;j++)
		{
				dMatData[i][j]=0;
		}
	 }
}

// copy constructor，
//拷贝构造函数的作用：
//（1）以类对象作为函数参数传值调用时;
//（2）函数返回值为类对象；
//（3）用一个已定义的对象去初始化一个新对象时；

CMatrix::CMatrix (const CMatrix& m)
{
   	iRow=m.Row();
	iCol=m.Col();
    dMatData = new double*[iRow];

	for (int i=0; i < iRow; i++)
	{
		dMatData[i]= new double[iCol];
	//	for(int j=0;j<iCol;j++)
		{
			memcpy(dMatData[i],m.dMatData[i],sizeof(double)*iCol);
		}
	 }
   
}

CMatrix::~CMatrix(void)
{
    for (int i=0; i < iRow; i++)
	{
		delete[] dMatData[i];
	 }
	delete[] dMatData;
}

//返回数组元素（引用返回）
double& CMatrix::operator () (int row, int col)
{
    if (row >= iRow || col >= iCol)
	{
      throw( "CMatrix::operator(): Index out of range!");
	}
	
    return dMatData[row][col]; 
}

////返回数组元素（重载）
double CMatrix::operator () (int row, int col) const
{
    if (row >= iRow || col >= iCol)
	{
      throw( "CMatrix::operator(): Index out of range!");
	}
	
    return dMatData[row][col]; 
}


//重载预算符+
CMatrix operator + (const CMatrix& m1,const CMatrix& m2)
{

   if((m1.Col()!=m2.Col()) ||(m1.Row()!=m2.Row()) )
   {
       throw( "CMatrix::operator+: The two matrix have different size!");
   }

   CMatrix matTmp(m1.Row(),m1.Col());
   for(int i=0;i<m1.Row();i++)
   {
	   for(int j=0;j<m1.Col();j++)
	   {
             matTmp(i,j)=m1(i,j)+m2(i,j);     
	   }
   }
   return matTmp;
}

//重载赋值运算符=，当左右两边矩阵的大小不相等时，
//以右边的大小为基准,调整左边矩阵的大小

CMatrix &CMatrix::operator = (const CMatrix& m) 
{
	//revised in 2011-4-1, by Daiwujiao
 //   if(iRow!=m.Row()||iCol!=m.Col())
	//{
 //       throw( "CMatrix::operator=: The two matrix have different size!");
	//}

	if(iRow!=m.Row()||iCol!=m.Col())
	{
		SetSize(m.Row(),m.Col());
	}
	for (int i=0; i < iRow; i++)
	{
		
		for(int j=0;j<iCol;j++)
		{
				dMatData[i][j]=m(i,j);
		}
	 }
    return *this;
}


//调整矩阵大小，原有值不变
void CMatrix::SetSize (int row, int col)
{
   if (row == iRow && col == iCol)
   {
      return;
   }

   double **rsData = new double*[row];
   	for (int i=0; i < row; i++)
	{
		rsData[i]= new double[col];
		for(int j=0;j<col;j++)
		{
				rsData[i][j]=0;
		}
	 }

	int minRow=(iRow>row)?row:iRow;
    int minCol= (iCol>col)?col:iCol;
    int  colSize = minCol * sizeof(double);
    

   for (int i=0; i < minRow; i++)
   {
      memcpy( rsData[i], dMatData[i], colSize);
   }

    for (int i=0; i < minRow; i++)
	{
         delete[] dMatData[i];
	}
	delete[] dMatData;
	dMatData=rsData;
    iRow=row;
	iCol=col;
    return;
}
//重载预算符-
CMatrix operator - (const CMatrix& m1,const CMatrix& m2)
{

   if((m1.Col()!=m2.Col()) ||(m1.Row()!=m2.Row()) )
   {
       throw( "CMatrix::operator-: The two matrix have different size!");
   }

   CMatrix matTmp(m1.Row(),m1.Col());
   for(int i=0;i<m1.Row();i++)
   {
	   for(int j=0;j<m1.Col();j++)
	   {
             matTmp(i,j)=m1(i,j)-m2(i,j);     
	   }
   }
   return matTmp;
}

//重载预算符*,两个矩阵相乘，m1的列要等于m2的行
CMatrix operator * (const CMatrix& m1,const CMatrix& m2)
{

   if((m1.Col()!=m2.Row()))
   {
       throw( "CMatrix::operator*: The col of matrix m1 doesn't equ to row of m2 !");
   }

   CMatrix matTmp(m1.Row(),m2.Col());
   for(int i=0;i<m1.Row();i++)
   {
	   for(int j=0;j<m2.Col();j++)
	   {
		   for(int k=0;k<m2.Row();k++)
		   {
             matTmp(i,j)+=m1(i,k)*m2(k,j);     
		   }
	   }
   }
   return matTmp;
}

//重载预算符*,矩阵右乘一个数
CMatrix operator * (const CMatrix& m1,const double& num)
{
   CMatrix matTmp(m1.Row(),m1.Col());
   for(int i=0;i<m1.Row();i++)
   {
	   for(int j=0;j<m1.Col();j++)
	   {
             matTmp(i,j)=m1(i,j)*num;     

	   }
   }
   return matTmp;
}

//重载预算符*,矩阵左乘一个数
CMatrix operator * (const double& num, const CMatrix& m1)
{
   CMatrix matTmp(m1.Row(),m1.Col());
   for(int i=0;i<m1.Row();i++)
   {
	   for(int j=0;j<m1.Col();j++)
	   {
             matTmp(i,j)=m1(i,j)*num;     
	   }
   }
   return matTmp;
}

//矩阵转置
CMatrix operator ~ (const CMatrix& m)
{
  CMatrix matTmp(m.Col(),m.Row());

   for (int i=0; i < m.Row(); i++)
      for (int j=0; j < m.Col(); j++)
      {
         matTmp(j,i) = m(i,j);
      }
   return matTmp;
}


//矩阵求逆
//采用选全主元法
CMatrix CMatrix::Inv()
{
    if (iRow!=iCol)
	{
        throw("待求逆的矩阵行列不相等!");
	}
    
    int i, j, k, vv;
 
    CMatrix InvMat(iRow,iRow);

    //复制矩阵
	InvMat=*this;
   
    int* MainRow=new int[iRow];
	int* MainCol=new int[iRow];//用于记录主元素的行和列

    double dMainCell;//主元元素的值
    double dTemp;//临时变量

    for(k = 0;k<iRow;k++)
	{
        dMainCell = 0;
        //选全主元
        for( i = k;i<iRow ;i++)
		{
            for( j = k;j<iRow;j++)
			{
                dTemp = fabs(InvMat(i, j));
                if(dTemp > dMainCell)
				{
                    dMainCell = dTemp;
                    MainRow[k] = i;
                    MainCol[k] = j;
				}
			}
		}

		if( fabs(dMainCell) < 0.0000000000001)//矩阵秩亏，不能求逆
		{
            throw("矩阵秩亏");
		}

        if(MainRow[k] != k)//交换行
		{
            for( j = 0 ;j<iRow;j++)
			{
                vv = MainRow[k];
                dTemp = InvMat(k, j);
                InvMat(k, j) = InvMat(vv, j);
                InvMat(vv, j) = dTemp;
			}
		}

        if(MainCol[k] != k)//交换列
		{
            for(i = 0;i<iRow;i++)
			{
                vv = MainCol[k];
                dTemp = InvMat(i, k);
                InvMat(i, k) = InvMat(i, vv);
                InvMat(i, vv) = dTemp;
			}
		}
        InvMat(k, k) = 1.0 / InvMat(k, k);//计算乘数

        for( j = 0;j< iRow;j++) //计算主行
		{
            if(j != k)
			{
                InvMat(k, j) = InvMat(k, j) * InvMat(k, k);
			}
		}
        for(i = 0;i<iRow;i++)//消元
		{
            if( i !=k)
			{
                for(j = 0;j<iRow;j++)
				{
					if(j != k)
					{
                        InvMat(i, j) -= InvMat(i, k) * InvMat(k, j);
					}
				}
			}
		}
        for( i = 0;i< iRow;i++ )//计算主列
		{
            if( i != k)
			{
				InvMat(i, k) = -InvMat(i, k) * InvMat(k, k);
			}
		}
	}

    for( k = iRow - 1;k>=0;k--)
	{
        if(MainCol[k] != k)// 交换行
		{
            for( j = 0;j<iRow;j++)
			{
                vv = MainCol[k];
                dTemp = InvMat(k, j);
                InvMat(k, j) = InvMat(vv, j);
                InvMat(vv, j) = dTemp;
			}
		}

        if(MainRow[k] != k)//交换列
		{
            for( i = 0;i<iRow;i++)
			{
				vv = MainRow[k];
                dTemp = InvMat(i, k);
                InvMat(i, k) = InvMat(i, vv);
                InvMat(i, vv) = dTemp;
			}
		}
	}
	delete[] MainRow;
	delete[] MainCol;
    return InvMat;
}
//单位化矩阵
void CMatrix::Unit()
{
     for(int i=0;i<iRow;i++)
	 {
		 for(int j=0;j<iCol;j++)
		 {
			 dMatData[i][j]=(i==j)?1:0;
		 }
	 }
}
void CMatrix::Allones()//生成全一矩阵
{
     for(int i=0;i<iRow;i++)
	 {
		 for(int j=0;j<iCol;j++)
		 {
			 dMatData[i][j]=1;
		 }
	 }
}
void CMatrix::Look()
{
	int iRow1=Row();
	int iCol2=Col();
	int **tmp=new int *[iRow1];    
    for(int i=0;i<iRow1;i++)
         tmp[i]= new int[iCol2];
	for(int i=0;i<iRow1;i++)
	{
		for(int j=0;j<iRow1;j++)
		{
			tmp[i][j]=dMatData[i][j];
		}
	}
	double t=tmp[0][0];
	   for(int i=0;i<iRow1;i++)
        delete[] tmp[i]; 
    delete[] tmp;
}