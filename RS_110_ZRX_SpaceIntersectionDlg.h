
// RS_110_ZRX_SpaceIntersectionDlg.h : ͷ�ļ�
//

#pragma once


// CRS_110_ZRX_SpaceIntersectionDlg �Ի���
class CRS_110_ZRX_SpaceIntersectionDlg : public CDialogEx
{
// ����
public:
	CRS_110_ZRX_SpaceIntersectionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RS_110_ZRX_SPACEINTERSECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strExample;
	afx_msg void OnBnClickedOk();
	CString strResult;
	afx_msg void OnBnClickedCancel();
};
