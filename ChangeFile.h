#pragma once
#include "afxdialogex.h"


// ChangeFile 对话框

class ChangeFile : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeFile)

public:
	ChangeFile(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChangeFile();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ChangeFile };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
