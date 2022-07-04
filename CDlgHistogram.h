#pragma once
#include "afxdialogex.h"


// CDlgHistogram 对话框



class CDlgHistogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgHistogram();
	int m_iLowGray, m_iUpGray;
	LONG m_lCount[256];
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAZhifang };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg
		void OnOK();
	BOOL OnInitDialog();
	void OnPaint();
	afx_msg void OnStnClickedCoor();
};
