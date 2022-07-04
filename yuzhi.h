#pragma once
#include "MFCTemplate.h"
#include "MFCTemplateDoc.h"
#include "MFCTemplateView.h"
// Yuzhifenge 对话框

class Yuzhifenge : public CDialogEx
{
	DECLARE_DYNAMIC(Yuzhifenge)

public:
	Yuzhifenge(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Yuzhifenge();
	CRect m_MouseRect;
	//标识是否拖动
	BOOL m_bIsDrawing;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Yuzhi };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_threshold;
	int m_GroupSelect;
	int temp1;
	int temp2;
	int temp3;
	int temp4;
	int ifyulan;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnBnClickedButtonyulan();
	afx_msg void OnBnClickedByl();
	CMFCTemplateDoc* pDoc;
	
	unsigned char* StartBits;
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	LONG lLineBytes;//每行
	afx_msg void OnBnClickedButtonhuifu();
	//afx_msg void OnBnClickedRadio4();
};
