
// MFCTemplateView.h: CMFCTemplateView 类的接口
//

#pragma once


class CMFCTemplateView : public CView
{
protected: // 仅从序列化创建
	CMFCTemplateView() noexcept;
	DECLARE_DYNCREATE(CMFCTemplateView)

// 特性
public:
	CMFCTemplateDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	static int WINAPI ThresholdDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes);
	static int WINAPI OTSUDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes);
	static void RegionSegAdaptive(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes);
	static BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2);
	static int WINAPI DF(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int bitcount);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCTemplateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDispimginfo();
	afx_msg void OnChangeLight();
	afx_msg void OnChangfile();
	afx_msg
		void LinerTrans(LPSTR lpSrcDibBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB);
	void OnPointinvert();
	afx_msg void OnVchange();
	afx_msg void OnShowhis();
	afx_msg void OnDaov();
	afx_msg void OnLchange();
	afx_msg void OnDaol();
	afx_msg void Onchange248();
	afx_msg void Onchange8c8g();
	afx_msg void OnXianxing();
	afx_msg void Onsmooth();
	afx_msg void Ongoos();
	afx_msg void Onmidvalue();
	afx_msg void Onlapulas();
	afx_msg void OnDiysmooth();
	afx_msg void Onlapulas1();
	afx_msg void Onlapulas2();
	afx_msg void Onsobel();
	afx_msg void Onrobert();
	afx_msg void Onxingtai();
	afx_msg void Onerzhi();
	afx_msg void Onyuzhi();
	afx_msg void Onwinchange();
	afx_msg void OnLashen();
	afx_msg void Onjunheng();
	afx_msg void OnMove();
	afx_msg void OnRevolve();
	afx_msg void OnMirrortrans();
	afx_msg void OnLvj();
	afx_msg void Onsumiao();
	afx_msg void Oncartoon();
	afx_msg void Onyouhua();
	afx_msg void Onshuiyin();
	afx_msg void Onjiema();
	afx_msg void Onuse();
	afx_msg void OnCanny();
	afx_msg void Ontst();
	afx_msg void Onimgzaoshengjy();
	afx_msg void Onimgzaoshengsj();
	afx_msg void OnMinlb();
	afx_msg void OnMaxlb();
};

#ifndef _DEBUG  // MFCTemplateView.cpp 中的调试版本
inline CMFCTemplateDoc* CMFCTemplateView::GetDocument() const
   { return reinterpret_cast<CMFCTemplateDoc*>(m_pDocument); }
#endif

