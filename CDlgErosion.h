#pragma once
#include "afxdialogex.h"


// CDlgErosion 对话框

class CDlgErosion : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgErosion)

public:
	CDlgErosion(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgErosion();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode1;
	int m_nMode2;
	CButton m_control1;
	CButton m_control2;
	CButton m_control3;
	CButton m_control4;
	CButton m_control5;
	CButton m_control6;
	CButton m_control7;
	CButton m_control8;
	CButton m_control9;
	int m_nstru1;
	int m_nstru2;
	int m_nstru3;
	int m_nstru4;
	int m_nstru5;
	int m_nstru6;
	int m_nstru7;
	int m_nstru8;
	int m_nstru9;
	afx_msg void OnBnClickedRadio7();
//	afx_msg void OnBnClickedRadio8();
//	afx_msg void OnBnClickedRadio9();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio15();
	afx_msg void OnBnClickedRadio16();
	afx_msg void OnBnClickedRadio17();
	afx_msg void OnBnClickedRadio18();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
};
