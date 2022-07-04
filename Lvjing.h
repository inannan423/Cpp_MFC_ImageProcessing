#pragma once
#include "afxdialogex.h"
#include "MFCTemplateDoc.h"

// Lvjing 对话框

class Lvjing : public CDialogEx
{
	DECLARE_DYNAMIC(Lvjing)

public:
	Lvjing(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Lvjing();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Lvj };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_operator1;
	float m_operator2;
	float m_operator3;
	float m_operator4;
	float m_operator5;
	float m_operator6;
	float m_operator7;
	float m_operator8;
	float m_operator9;
	double m_coefficient;
	int m_constant;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedRadio1();
	CButton m_filter1_Control;
	int m_filter_species;
	afx_msg void OnBnClickedRadiosp();
	CButton m_filter8_Control;
	int m_edge_direction;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadiorh();
	afx_msg void OnBnClickedRadiofd();
	afx_msg void OnBnClickedRadiosob();
	
	afx_msg void OnBnClickedRadiop();
	afx_msg void OnBnClickedRadiocz();

	//BOOL OnInitDialog();
	//BOOL OnInitDialog();
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	unsigned char* beginBits;
	CMFCTemplateDoc* pDoc;
	CEdit suanzi1;
	CEdit suanzi2;
	CEdit suanzi3;
	CEdit suanzi4;
	CEdit suanzi5;
	CEdit suanzi6;
	CEdit suanzi7;
	CEdit suanzi8;
	CEdit suanzi9;
	CEdit suanzi10;
	CEdit suanzi11;
	afx_msg void OnBnClickedsuanzi();
	virtual BOOL OnInitDialog();
	CButton suanz;
	CButton clicklight;
	afx_msg void OnBnClickedlight();
	
};
