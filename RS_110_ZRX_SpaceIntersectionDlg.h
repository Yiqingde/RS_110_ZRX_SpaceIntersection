
// RS_110_ZRX_SpaceIntersectionDlg.h : 头文件
//

#pragma once


// CRS_110_ZRX_SpaceIntersectionDlg 对话框
class CRS_110_ZRX_SpaceIntersectionDlg : public CDialogEx
{
// 构造
public:
	CRS_110_ZRX_SpaceIntersectionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RS_110_ZRX_SPACEINTERSECTION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
