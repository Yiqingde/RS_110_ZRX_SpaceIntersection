
// RS_110_ZRX_OrientationOfRe_ObDlg.h : ͷ�ļ�
//

#pragma once


// CRS_110_ZRX_OrientationOfRe_ObDlg �Ի���
class CRS_110_ZRX_OrientationOfRe_ObDlg : public CDialogEx
{
// ����
public:
	CRS_110_ZRX_OrientationOfRe_ObDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RS_110_ZRX_ORIENTATIONOFRE_OB_DIALOG };

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
	afx_msg void OnBnClickedOk();
};
