/***************************************************************************
*  �ļ���:<RS_110_ZRX_SpaceIntersectionDlg.cpp>                            *
*                                                                          *
*  ����: Dialog�Ի���ʹ��                                                  *
*                                                                          *
*  ��ʷ��**����**         **����**            **ǩ��**                     *
*      2019��4��19��        ����              �����                       *
*                                                                          *
*  �ⲿ���̣�                                                              *
*                                                                          *
/**************************************************************************/
// RS_110_ZRX_SpaceIntersectionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RS_110_ZRX_SpaceIntersection.h"
#include "RS_110_ZRX_SpaceIntersectionDlg.h"
#include "afxdialogex.h"
#include "Support.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRS_110_ZRX_SpaceIntersectionDlg �Ի���




CRS_110_ZRX_SpaceIntersectionDlg::CRS_110_ZRX_SpaceIntersectionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRS_110_ZRX_SpaceIntersectionDlg::IDD, pParent)
	, strExample(_T(""))
	, strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRS_110_ZRX_SpaceIntersectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_strExample, strExample);
	DDX_Text(pDX, IDC_EDIT1_strResult, strResult);
}

BEGIN_MESSAGE_MAP(CRS_110_ZRX_SpaceIntersectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRS_110_ZRX_SpaceIntersectionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRS_110_ZRX_SpaceIntersectionDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRS_110_ZRX_SpaceIntersectionDlg ��Ϣ�������

BOOL CRS_110_ZRX_SpaceIntersectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CRS_110_ZRX_SpaceIntersectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRS_110_ZRX_SpaceIntersectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRS_110_ZRX_SpaceIntersectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//���㰴ť
void CRS_110_ZRX_SpaceIntersectionDlg::OnBnClickedOk()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	UpdateData(true);
	CSupport k;
	k.main(strExample,strResult);
	UpdateData(false);
}


//ȡ����ť
void CRS_110_ZRX_SpaceIntersectionDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
