#pragma once
#include "afxdialogex.h"


// Revolve 对话框

class Revolve : public CDialogEx
{
	DECLARE_DYNAMIC(Revolve)

public:
	Revolve(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Revolve();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int dushu;
	afx_msg void OnEnChangeEdit1();
};
