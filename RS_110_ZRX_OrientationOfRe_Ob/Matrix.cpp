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

// copy constructor��
//�������캯�������ã�
//��1�����������Ϊ����������ֵ����ʱ;
//��2����������ֵΪ�����
//��3����һ���Ѷ���Ķ���ȥ��ʼ��һ���¶���ʱ��

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

//��������Ԫ�أ����÷��أ�
double& CMatrix::operator () (int row, int col)
{
    if (row >= iRow || col >= iCol)
	{
      throw( "CMatrix::operator(): Index out of range!");
	}
	
    return dMatData[row][col]; 
}

////��������Ԫ�أ����أ�
double CMatrix::operator () (int row, int col) const
{
    if (row >= iRow || col >= iCol)
	{
      throw( "CMatrix::operator(): Index out of range!");
	}
	
    return dMatData[row][col]; 
}


//����Ԥ���+
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

//���ظ�ֵ�����=�����������߾���Ĵ�С�����ʱ��
//���ұߵĴ�СΪ��׼,������߾���Ĵ�С

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


//���������С��ԭ��ֵ����
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
//����Ԥ���-
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

//����Ԥ���*,����������ˣ�m1����Ҫ����m2����
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

//����Ԥ���*,�����ҳ�һ����
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

//����Ԥ���*,�������һ����
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

//����ת��
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


//��������
//����ѡȫ��Ԫ��
CMatrix CMatrix::Inv()
{
    if (iRow!=iCol)
	{
        throw("������ľ������в����!");
	}
    
    int i, j, k, vv;
 
    CMatrix InvMat(iRow,iRow);

    //���ƾ���
	InvMat=*this;
   
    int* MainRow=new int[iRow];
	int* MainCol=new int[iRow];//���ڼ�¼��Ԫ�ص��к���

    double dMainCell;//��ԪԪ�ص�ֵ
    double dTemp;//��ʱ����

    for(k = 0;k<iRow;k++)
	{
        dMainCell = 0;
        //ѡȫ��Ԫ
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

		if( fabs(dMainCell) < 0.0000000000001)//�����ȿ�����������
		{
            throw("�����ȿ�");
		}

        if(MainRow[k] != k)//������
		{
            for( j = 0 ;j<iRow;j++)
			{
                vv = MainRow[k];
                dTemp = InvMat(k, j);
                InvMat(k, j) = InvMat(vv, j);
                InvMat(vv, j) = dTemp;
			}
		}

        if(MainCol[k] != k)//������
		{
            for(i = 0;i<iRow;i++)
			{
                vv = MainCol[k];
                dTemp = InvMat(i, k);
                InvMat(i, k) = InvMat(i, vv);
                InvMat(i, vv) = dTemp;
			}
		}
        InvMat(k, k) = 1.0 / InvMat(k, k);//�������

        for( j = 0;j< iRow;j++) //��������
		{
            if(j != k)
			{
                InvMat(k, j) = InvMat(k, j) * InvMat(k, k);
			}
		}
        for(i = 0;i<iRow;i++)//��Ԫ
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
        for( i = 0;i< iRow;i++ )//��������
		{
            if( i != k)
			{
				InvMat(i, k) = -InvMat(i, k) * InvMat(k, k);
			}
		}
	}

    for( k = iRow - 1;k>=0;k--)
	{
        if(MainCol[k] != k)// ������
		{
            for( j = 0;j<iRow;j++)
			{
                vv = MainCol[k];
                dTemp = InvMat(k, j);
                InvMat(k, j) = InvMat(vv, j);
                InvMat(vv, j) = dTemp;
			}
		}

        if(MainRow[k] != k)//������
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
//��λ������
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
void CMatrix::Allones()//����ȫһ����
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