#pragma once
#include "afxdialogex.h"


// yinxie 对话框

class yinxie : public CDialogEx
{
	DECLARE_DYNAMIC(yinxie)

public:
	yinxie(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~yinxie();
	int num = 0;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
};
