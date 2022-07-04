#pragma once

#include "MFCTemplate.h"
#include "MFCTemplateDoc.h"
// Windowchange 对话框

class Windowchange : public CDialogEx
{
	DECLARE_DYNAMIC(Windowchange)

public:
	Windowchange(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Windowchange();
	int m_iIsDraging;
	CRect m_MouseRect;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Winchange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BYTE m_bUp;
	BYTE m_bLow;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtony();

	CMFCTemplateDoc* pDoc;

	unsigned char* StartBits;
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	LONG lLineBytes;//每行
	afx_msg void OnBnClickedButtonh();
};
