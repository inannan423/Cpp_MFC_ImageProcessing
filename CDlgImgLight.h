#pragma once
#include "afxdialogex.h"


// CDlgImgLight 对话框

class CDlgImgLight : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgLight)

public:
	CDlgImgLight(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgImgLight();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_InputChanglight };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	long Lightness;
	virtual BOOL OnInitDialog();
};
