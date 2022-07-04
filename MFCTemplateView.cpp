
// MFCTemplateView.cpp: CMFCTemplateView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCTemplate.h"
#include <time.h>
#endif

#include "MFCTemplateDoc.h"
#include "MFCTemplateView.h"
#include <opencv2/opencv.hpp>
//#include "xphoto/oilpainting.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW	
#endif
#include "CDlgImgInfo.h"
#include "CDlgImgLight.h"
#include <iostream>
#include "CDlgHistogram.h"
#include "Dib.h"
#include "DIBAPI.H"
//引入opencv


using namespace cv;

using namespace std;
// CMFCTemplateView
std::vector<cv::Mat> planes;
cv::Mat complexImage;

IMPLEMENT_DYNCREATE(CMFCTemplateView, CView)

BEGIN_MESSAGE_MAP(CMFCTemplateView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DispImgInfo, &CMFCTemplateView::OnDispimginfo)
	ON_COMMAND(ID_ChangeLightness, &CMFCTemplateView::OnChangeLight)
	ON_COMMAND(ID_ChangFile, &CMFCTemplateView::OnChangfile)
	ON_COMMAND(ID_PointInvert, &CMFCTemplateView::OnPointinvert)
	ON_COMMAND(ID_V_change, &CMFCTemplateView::OnVchange)
	ON_COMMAND(ID_ShowHis, &CMFCTemplateView::OnShowhis)
	ON_COMMAND(ID_DaoV, &CMFCTemplateView::OnDaov)
	ON_COMMAND(ID_LChange, &CMFCTemplateView::OnLchange)
	ON_COMMAND(ID_DaoL, &CMFCTemplateView::OnDaol)
	ON_COMMAND(ID_change24_8, &CMFCTemplateView::Onchange248)
	ON_COMMAND(ID_change8c8g, &CMFCTemplateView::Onchange8c8g)
	ON_COMMAND(ID_Xianxing, &CMFCTemplateView::OnXianxing)
	ON_COMMAND(ID_smooth, &CMFCTemplateView::Onsmooth)
	ON_COMMAND(ID_goos, &CMFCTemplateView::Ongoos)
	ON_COMMAND(ID_midvalue, &CMFCTemplateView::Onmidvalue)
	ON_COMMAND(ID_DIYsmooth, &CMFCTemplateView::OnDiysmooth)
	ON_COMMAND(ID_lapulas1, &CMFCTemplateView::Onlapulas1)
	ON_COMMAND(ID_lapulas2, &CMFCTemplateView::Onlapulas2)
	ON_COMMAND(ID_sobel, &CMFCTemplateView::Onsobel)
	ON_COMMAND(ID_robert, &CMFCTemplateView::Onrobert)
	ON_COMMAND(ID_xingtai, &CMFCTemplateView::Onxingtai)
	ON_COMMAND(ID_erzhi, &CMFCTemplateView::Onerzhi)
	ON_COMMAND(ID_yuzhi, &CMFCTemplateView::Onyuzhi)
	ON_COMMAND(ID_winchange, &CMFCTemplateView::Onwinchange)
	ON_COMMAND(ID_Lashen, &CMFCTemplateView::OnLashen)
	ON_COMMAND(ID_junheng, &CMFCTemplateView::Onjunheng)
	ON_COMMAND(ID_Move, &CMFCTemplateView::OnMove)
	ON_COMMAND(ID_Revolve, &CMFCTemplateView::OnRevolve)
	ON_COMMAND(ID_MirrorTrans, &CMFCTemplateView::OnMirrortrans)
	ON_COMMAND(ID_Lvj, &CMFCTemplateView::OnLvj)
	ON_COMMAND(ID_sumiao, &CMFCTemplateView::Onsumiao)
	ON_COMMAND(ID_cartoon, &CMFCTemplateView::Oncartoon)
	ON_COMMAND(ID_youhua, &CMFCTemplateView::Onyouhua)
	ON_COMMAND(ID_shuiyin, &CMFCTemplateView::Onshuiyin)
	ON_COMMAND(ID_jiema, &CMFCTemplateView::Onjiema)
	ON_COMMAND(ID_use, &CMFCTemplateView::Onuse)
	ON_COMMAND(ID_Canny, &CMFCTemplateView::OnCanny)
	//ON_COMMAND(ID_tst, &CMFCTemplateView::Ontst)
	ON_COMMAND(ID_imgzaoshengjy, &CMFCTemplateView::Onimgzaoshengjy)
	ON_COMMAND(ID_imgzaoshengsj, &CMFCTemplateView::Onimgzaoshengsj)
	ON_COMMAND(ID_MinLb, &CMFCTemplateView::OnMinlb)
	ON_COMMAND(ID_MaxLb, &CMFCTemplateView::OnMaxlb)
END_MESSAGE_MAP()

// CMFCTemplateView 构造/析构

CMFCTemplateView::CMFCTemplateView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCTemplateView::~CMFCTemplateView()
{
}

BOOL CMFCTemplateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCTemplateView 绘图

void CMFCTemplateView::OnDraw(CDC* pDC)
{
	CMFCTemplateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//以上部分用原有内容，根据项目名称不同
	// TODO: 在此处为本机数据添加绘制代码
	HGLOBAL hDIB = pDoc->GetHObject();

	// 判断DIB是否为空
	if (hDIB != NULL)
	{
		LPSTR lpSrcDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// 获取DIB宽度
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpSrcDibSection);

		// 获取DIB高度
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpSrcDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// 输出DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}
}


// CMFCTemplateView 打印

BOOL CMFCTemplateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCTemplateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCTemplateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCTemplateView 诊断

#ifdef _DEBUG
void CMFCTemplateView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTemplateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTemplateDoc* CMFCTemplateView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTemplateDoc)));
	return (CMFCTemplateDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTemplateView 消息处理程序




void CMFCTemplateView::OnDispimginfo()
{
	// 显示图像基本信息
	CMFCTemplateDoc * pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		   AfxMessageBox(L"对不起，不是256色位图！");// 警告
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
		   return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回
	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
/////////////////////////////////////////////////////////////////////////////////////////////////	
	CDlgImgInfo dlgPara;// 创建对话框		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;

	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定


}


//调整亮度
void CMFCTemplateView::OnChangeLight()
{
	// TODO: 在此添加命令处理程序代码
	unsigned char* lpSrcData=0;
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;



	/*

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}*/										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	CDlgImgLight dlgPara;// 创建对话框	

	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	int page = 1;
	if (lpSrcBitCount == 24) page = 3;
	if (lpSrcBitCount == 8) page = 1;
	int changing = dlgPara.Lightness;
	//std::cout << changing;
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++) {
			for (int l = 0; l < page; l++) {
				lpSrcData = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * page + l;
				int temp = *lpSrcData + changing;
				if (temp < 0) {
					*lpSrcData = 0;
				}
				else if (temp > 255) {
					*lpSrcData = 255;
				}
				else {
					*lpSrcData = (unsigned char)(temp + 0.5);
				}
			}
			
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	//在视窗更新图片
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	UpdateData(true);
	
}

void CMFCTemplateView::OnChangfile()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);

	pDoc->OnOpenDocument(pDoc->GetPathName());
	//获取文件路径名
	pDoc->SetModifiedFlag(true);//标记修改

	pDoc->UpdateAllViews(NULL);
	//是否保存修改后的图片
	//AfxMessageBox(L"已与后台图像交换");
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


//反色
void CMFCTemplateView::OnPointinvert()
{
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	-128~127
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);
	float fa = -1.0;
	float fb = 255;
	FLOAT	temp;//中间变量
	//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);
	for (int i = 0; i < lSrcHeight; i++)
	{
		for (int j = 0; j < lSrcWidth; j++){
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			temp = fa * (*lpSrc) + fb;

			// 判断是否超出范围
			if (temp > 255){
				*lpSrc = 255;
			}
			else if (temp < 0){
				*lpSrc = 0;
			}
			else{
				*lpSrc = (unsigned char)(temp + 0.5);
			}
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

#include "Vchange.h"
//V变换
void CMFCTemplateView::OnVchange()
{
	// TODO: 在此添加命令处理程序代码
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	-128~127
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);
	//调用函数处理，图像反色
	int threshold = 10;//这里等待添加窗口
	Vchange dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	threshold = dlgPara.m_middle;
	delete dlgPara;

	if (*lpSrcStartBits < 128)
	{
		FLOAT fa1 = 2.0;
		FLOAT fb1 = 0;
		FLOAT	temp;//中间变量
	//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa1 * (*lpSrc) + fb1;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	else
	{
		FLOAT fa2 = -2.0;
		FLOAT fb2 = 510;
		FLOAT	temp;//中间变量
	//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa2 * (*lpSrc) + fb2;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//直方图
void CMFCTemplateView::OnShowhis()
{
	
	// TODO: 在此添加命令处理程序代码
	// 简单显示直方图
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	-128~127
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);
	// 获取文档
	//CMFCTemplateDoc* pDoc = GetDocument();




	LONG i, j;
	LONG m_lCount[256];


	// 锁定DIB
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	if (lpSrcDib == NULL)
	{
		AfxMessageBox(L"先打开图像");
		return;
	}
	// 更改光标形状
	BeginWaitCursor();
	//计算直方图
	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		m_lCount[i] = 0;
	}

	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * i + j;
			// 计数加1
			m_lCount[*(lpSrc)]++;
		}
	}
	// 创建对话框
	CDlgHistogram dlgHist;
	// 初始化变量值
	dlgHist.m_iLowGray = 0;
	dlgHist.m_iUpGray = 255;
	for (i = 0; i < 256; i++)
	{
		dlgHist.m_lCount[i] = m_lCount[i];
	}
	// 显示对话框
	if (dlgHist.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
	
}

#include "DaoV.h"
void CMFCTemplateView::OnDaov()
{
	// 指向源图像的指针
	unsigned char* lpSrc = 0;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;          //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	int threshold = 10;//这里等待添加窗口

	DaoV dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	threshold = dlgPara.m_middle;
	delete dlgPara;

	int type = 1;
	//DaoV::Segmental2_Linear_Tran(lpSrcStartBits, lSrcWidth, lSrcHeight, type, threshold);//分段线性变换
	// 中间变量
	FLOAT	fTemp, fA1 = 1, fB1 = 0, fA2 = 1, fB2 = 0;
	//中间灰度
	int seg_gray = 127;
	
	//计算线性变换的参数
	if (type == 1)//倒V字型
	{
		fA1 = (float)(255 / threshold);//2.0 if threshold==128;
		fB1 = 0;  //(2f)
		fA2 = -(float)(255 / threshold);//-2.0 if threshold==128;
		fB1 = (float)(255 + (255 * threshold) / (255 - threshold));//(-2f+2*255)  if threshold==128;
	}
	
	// 每行
	int i, j;
	for (i = 0; i < lSrcHeight; i++)
	{
		// 每列
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;

			// 线性变换,分段
			if (*lpSrc >= 0 && *lpSrc <= seg_gray)
				fTemp = fA1 * (*lpSrc) + fB1;
			if (*lpSrc >= seg_gray + 1 && *lpSrc <= 255)
				fTemp = fA2 * (*lpSrc) + fB2;

			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char)(fTemp + 0.5);
			}
		}
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//Invalidate();  //OK
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	
}

#include "LChange.h"
void CMFCTemplateView::OnLchange()
{
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{		
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		   ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定		
		return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	//调用函数处理，图像反色
	int threshold = 10;//这里等待添加窗口
	Lchange dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	threshold = dlgPara.m_middle;
	delete dlgPara;

	if (*lpSrcStartBits < 128)
	{
		FLOAT fa = 2;
		FLOAT fb = 0;
		//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA1, fB1);
		FLOAT	temp;//中间变量
		//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa * (*lpSrc) + fb;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	else
	{
		FLOAT fa1 = 0;
		FLOAT fb1 = 255;
		//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA2, fB2);
		FLOAT	temp;//中间变量
		//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa1 * (*lpSrc) + fb1;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

#include "DaoL.h"
//倒L变换
void CMFCTemplateView::OnDaol()
{
	// TODO: 在此添加命令处理程序代码
	unsigned char* lpSrc;
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	////////////////////////////////////////////////////////////////////////////////////////////////	
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{		
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
	    ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定		
		return;									//返回
	 }										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	//调用函数处理，图像反色
	int threshold = 10;//这里等待添加窗口
	DaoL dlgPara;
	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		return;
	}
	threshold = dlgPara.m_middle;
	delete dlgPara;
	if (*lpSrcStartBits < 128)
	{
		FLOAT fa1 = -2;
		FLOAT fb1 = 255;
		FLOAT	temp;//中间变量
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa1 * (*lpSrc) + fb1;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	else
	{
		FLOAT fa2 = 0;
		FLOAT fb2 = 0;
		FLOAT	temp;//中间变量
		for (int i = 0; i < lSrcHeight; i++)
		{
			for (int j = 0; j < lSrcWidth; j++) {
				lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
				temp = fa2 * (*lpSrc) + fb2;

				// 判断是否超出范围
				if (temp > 255) {
					*lpSrc = 255;
				}
				else if (temp < 0) {
					*lpSrc = 0;
				}
				else {
					*lpSrc = (unsigned char)(temp + 0.5);
				}
			}
		}
	}
	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}

//24位彩色转灰度
void CMFCTemplateView::Onchange248()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lWidth;      //图象的宽度和高度
	long	lHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	int threshold;
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	long i, j;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * lpSrcBitCount);		// 计算图象每行的字节数

	BITMAPINFOHEADER* pHead;
	RGBQUAD* pColorTable;
	int lineByteNew;
	int biBitCount = 8;
	lineByteNew = (lWidth * biBitCount / 8 + 3) / 4 * 4;
	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char* pBmpBufNew;
	pBmpBufNew = new unsigned char[lineByteNew * lHeight + sizeof(BITMAPINFOHEADER) + 256 * 4];//申请新图像的空间
	memcpy(pBmpBufNew, (unsigned char*)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝
	pHead = (BITMAPINFOHEADER*)pBmpBufNew;
	pHead->biBitCount = 8;//改变位数,
	pHead->biHeight = lHeight;
	pHead->biWidth = lWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew * lHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;
	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));
	//灰度图像有颜色表，且颜色表表项为
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，给颜色表赋值
		for (int i = 0; i < 256; i++)
		{
			pColorTable[i].rgbBlue = i;
			pColorTable[i].rgbGreen = i;
			pColorTable[i].rgbRed = i;
			pColorTable[i].rgbReserved = 0;
		}
	}

	int Red, Green, Blue, Gray, offset;
	offset = sizeof(BITMAPINFOHEADER) + 256 * 4;
	//逐行扫描
	for (i = 0; i < lHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lHeight - 1 - i) + j * 3;
			Blue = *lpSrc;
			Green = *(++lpSrc);
			Red = *(++lpSrc);
			Gray = (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// 变换
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lHeight - 1 - i) + j;
			*lpSrc = Gray;
		}
	}
	//拷贝
	memcpy(lpSrcDib, pBmpBufNew, lineByteNew * lHeight + sizeof(BITMAPINFOHEADER) + 256 * 4);

	delete[]pBmpBufNew;

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//Invalidate();  //OK
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}



void CMFCTemplateView::Onchange8c8g()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	int threshold;
	unsigned char* lpSrc;
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	long i, j;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数

	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回


	// 灰度映射表
	BYTE bMap[256];
	RGBQUAD* pTable, * pTable1;
	pTable = (RGBQUAD*)(lpSrcDib + sizeof(BITMAPINFOHEADER));
	//新的调色板
	for (i = 0; i < 256; i++) {
		bMap[i] = (BYTE)(0.299 * pTable->rgbRed + 0.587 * pTable->rgbGreen + 0.114 * pTable->rgbBlue + 0.5);
		pTable->rgbRed = (BYTE)i;
		pTable->rgbGreen = (BYTE)i;
		pTable->rgbBlue = (BYTE)i;
		pTable->rgbReserved = (BYTE)0;
		pTable++;
	}
	//逐行扫描，更换每个像素的颜色索引（即按照灰度映射表换成灰度值）
	for (i = 0; i < lSrcHeight; i++)
	{
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向原图的第i行，第j个像素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			*lpSrc = bMap[*lpSrc];
		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}



#include "CDlgLinerPara.h"
void CMFCTemplateView::OnXianxing()
{
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{		
		//AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		  // ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定		
		//return;									//返回
	 //}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////	

	xianxinbianhuan dlgPara;
	float fA, fB;

	dlgPara.m_fA = 2.0;
	dlgPara.m_fB = -128.0;

	if (dlgPara.DoModal() != IDOK)
	{
		return;
	}

	fA = dlgPara.m_fA;
	fB = dlgPara.m_fB;
	FLOAT	temp;//中间变量
	delete dlgPara;

	//更改光标形状
	BeginWaitCursor();

	//LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fA, fB);
	for (int i = 0; i < lSrcHeight; i++)
	{
		for (int j = 0; j < lSrcWidth; j++) {
			lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			temp = fA * (*lpSrc) + fB;

			// 判断是否超出范围
			if (temp > 255) {
				*lpSrc = 255;
			}
			else if (temp < 0) {
				*lpSrc = 0;
			}
			else {
				*lpSrc = (unsigned char)(temp + 0.5);
			}
		}
	}
	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	//恢复光标
	EndWaitCursor();
}

#include "Template.h"
void CMFCTemplateView::Onsmooth()
{
	// TODO: 在此添加命令处理程序代码
	int m_x = 1;
	int m_y = 1;

	float m_C = (FLOAT)(1.0 / 9.0);

	// 更新文本框状态
	int m_1 = 1;
	int m_2 = 1;
	int m_3 = 1;
	int m_4 = 1;
	int m_5 = 1;
	int m_6 = 1;
	int m_7 = 1;
	int m_8 = 1;
	int m_9 = 1;
	//UpdateData(FALSE);
	//
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	LPSTR	lpDIB;

	// 指向DIB像素指针
	LPSTR   lpDIBBits;

	int TempHeight;
	int TempWidth;
	FLOAT fTempC;
	int TempX;
	int TempY;
	FLOAT aValue[9];

	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素
	int lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);
	///////////////////

	aValue[0] = m_1;
	aValue[1] = m_2;
	aValue[2] = m_3;
	aValue[3] = m_4;
	aValue[4] = m_5;
	aValue[5] = m_6;
	aValue[6] = m_7;
	aValue[7] = m_8;
	aValue[8] = m_9;

	// 设定平移量（3*3）
	TempHeight = 3;
	TempWidth = 3;
	TempX = m_x;
	TempY = m_y;
	fTempC = (FLOAT)(1.0 / 9.0);
	BeginWaitCursor();
	///////////////////////////
	if (::Template(lpDIBBits, lSrcWidth, lSrcHeight, TempHeight, TempWidth, TempX, TempY, aValue, fTempC))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		AfxMessageBox(L"分配内存失败！系统提示");// 警告
	}
	AfxMessageBox(L"均值滤波操作完成！");
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

//均值滤波
void CMFCTemplateView::Ongoos()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档
	LPSTR	lpDIB;     // 指向DIB的指针
	LPSTR   lpDIBBits;// 指向DIB像素指针
	int TempHeight;      // 模板高度
	int TempWidth;      // 模板宽度
	FLOAT fTempC;    // 模板系数
	int TempX;     // 模板中心元素X坐标
	int TempY;     // 模板中心元素Y坐标
	FLOAT aValue[9]; // 模板元素数组

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像像素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 提示用户

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

		return;                                         // 返回
	}

	// 给模板数组赋初值（为平均模板）
	aValue[0] = 1.0;
	aValue[1] = 2.0;
	aValue[2] = 1.0;
	aValue[3] = 2.0;
	aValue[4] = 4.0;
	aValue[5] = 2.0;
	aValue[6] = 1.0;
	aValue[7] = 2.0;
	aValue[8] = 1.0;

	// 设定平移量（3*3）
	TempHeight = 3;
	TempWidth = 3;
	TempX = 1;
	TempY = 1;
	fTempC = (FLOAT)(1.0 / 16.0);

	// 更改光标形状
	BeginWaitCursor();

	// 调用Template()函数平滑DIB
	if (Template(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB), TempHeight, TempWidth, TempX, TempY, aValue, fTempC))
	{
		pDoc->SetModifiedFlag(TRUE);// 设置脏标记

		pDoc->UpdateAllViews(NULL);// 更新视图
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}
	AfxMessageBox(L"高斯滤波操作完成！");
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}

//中值滤波
void CMFCTemplateView::Onmidvalue()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档
	LPSTR	lpDIB;     // 指向DIB的指针
	LPSTR   lpDIBBits;// 指向DIB像素指针
	int iFilterH;// 滤波器的高度
	int iFilterW;// 滤波器的宽度
	int iFilterMX;// 中心元素的X坐标
	int iFilterMY;// 中心元素的Y坐标

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());

	// 找到DIB图像像素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的中值滤波，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 提示用户

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

		return;                                         // 返回
	}

	// 初始化变量值
	iFilterH = 3;
	iFilterW = 1;
	iFilterMX = 0;
	iFilterMY = 1;

	// 更改光标形状
	BeginWaitCursor();

	// 调用MedianFilter()函数中值滤波
	if (MedianFilter(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB), pDoc->m_dib.GetHeight(lpDIB), iFilterH, iFilterW, iFilterMX, iFilterMY))
	{

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// 提示用户
		AfxMessageBox(L"分配内存失败！");
	}
	AfxMessageBox(L"中值滤波操作完成！");
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}



void CMFCTemplateView::Onlapulas1()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	LPSTR	lpDIB;

	// 指向DIB像素指针
	LPSTR   lpDIBBits;

	int TempHeight;
	int TempWidth;
	FLOAT fTempC;
	int TempX;
	int TempY;
	FLOAT aValue[9];

	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素
	int lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);
	///////////////////

	// 设定平移量（3*3）
	TempWidth = 3;
	TempHeight = 3;
	fTempC = 1.0;
	TempX = 1;
	TempY = 1;
	aValue[0] = 0;
	aValue[1] = -1.0;
	aValue[2] = 0;
	aValue[3] = -1.0;
	aValue[4] = 5.0;
	aValue[5] = -1.0;
	aValue[6] = 0;
	aValue[7] = -1.0;
	aValue[8] = 0;
	///////////////////////////
	if (::Template(lpDIBBits, lSrcWidth, lSrcHeight, TempHeight, TempWidth, TempX, TempY, aValue, fTempC))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		AfxMessageBox(L"分配内存失败！系统提示");// 警告
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

#include "Smooth.h"
void CMFCTemplateView::OnDiysmooth()
{
	// TODO: 在此添加命令处理程序代码

	// 图像平滑



	// 获取文档

	CMFCTemplateDoc* pDoc = GetDocument();



	// 指向DIB的指针

	LPSTR	lpDIB;



	// 指向DIB像素指针

	LPSTR   lpDIBBits;



	// 模板高度

	int		TempHeight;



	// 模板宽度

	int		TempWidth;



	// 模板系数

	FLOAT	fTempC;



	// 模板中心元素X坐标

	int		TempX;



	// 模板中心元素Y坐标

	int		TempY;



	// 模板元素数组

	FLOAT	aValue[25];



	// 锁定DIB

	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB



	// 找到DIB图像像素起始位置

	//lpDIBBits = ::FindDIBBits(lpDIB);
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素


	// 判断是否是8-bpp位图（这里为了方便，只处理8-bpp位图的平滑，其它的可以类推）

	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 提示用户

		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定

		return;                                         // 返回
	}



	// 创建对话框

	CDlgSmooth dlgPara;



	// 给模板数组赋初值（为平均模板）

	aValue[0] = 1.0;

	aValue[1] = 1.0;

	aValue[2] = 1.0;

	aValue[3] = 0.0;

	aValue[4] = 0.0;

	aValue[5] = 1.0;

	aValue[6] = 1.0;

	aValue[7] = 1.0;

	aValue[8] = 0.0;

	aValue[9] = 0.0;

	aValue[10] = 1.0;

	aValue[11] = 1.0;

	aValue[12] = 1.0;

	aValue[13] = 0.0;

	aValue[14] = 0.0;

	aValue[15] = 0.0;

	aValue[16] = 0.0;

	aValue[17] = 0.0;

	aValue[18] = 0.0;

	aValue[19] = 0.0;

	aValue[20] = 0.0;

	aValue[21] = 0.0;

	aValue[22] = 0.0;

	aValue[23] = 0.0;

	aValue[24] = 0.0;



	// 初始化对话框变量值

	dlgPara.m_intType = 0;

	dlgPara.m_iTempH = 3;

	dlgPara.m_iTempW = 3;

	dlgPara.m_iTempMX = 1;

	dlgPara.m_iTempMY = 1;

	dlgPara.m_fTempC = (FLOAT)(1.0 / 9.0);

	dlgPara.m_Arr = aValue;



	// 显示对话框，提示用户设定平移量

	if (dlgPara.DoModal() != IDOK)

	{

		// 返回

		return;

	}



	// 获取用户设定的平移量

	TempHeight = dlgPara.m_iTempH;

	TempWidth = dlgPara.m_iTempW;

	TempX = dlgPara.m_iTempMX;

	TempY = dlgPara.m_iTempMY;

	fTempC = dlgPara.m_fTempC;



	// 删除对话框

	delete dlgPara;



	// 更改光标形状

	BeginWaitCursor();

	int lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);

	// 调用Template()函数平滑DIB

	if (::Template(lpDIBBits, lSrcWidth, lSrcHeight,

		TempHeight, TempWidth, TempX, TempY, aValue, fTempC))

	{
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);

	}

	else

	{
		// 提示用户

		AfxMessageBox(L"内存分配失败");// 提示用户

	}



	// 解除锁定

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定



	// 恢复光标

	EndWaitCursor();


}





void CMFCTemplateView::Onlapulas2()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	LPSTR	lpDIB;

	// 指向DIB像素指针
	LPSTR   lpDIBBits;

	int TempHeight;
	int TempWidth;
	FLOAT fTempC;
	int TempX;
	int TempY;
	FLOAT aValue[9];

	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素
	int lSrcWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lSrcHeight = pDoc->m_dib.GetHeight(lpDIB);
	///////////////////

	// 设定平移量（3*3）
	TempWidth = 3;
	TempHeight = 3;
	fTempC = 1.0;
	TempX = 1;
	TempY = 1;
	aValue[0] = -1.0;
	aValue[1] = -1.0;
	aValue[2] = -1.0;
	aValue[3] = -1.0;
	aValue[4] = 8.0;
	aValue[5] = -1.0;
	aValue[6] = -1.0;
	aValue[7] = -1.0;
	aValue[8] = -1.0;
	///////////////////////////
	if (::Template(lpDIBBits, lSrcWidth, lSrcHeight, TempHeight, TempWidth, TempX, TempY, aValue, fTempC))
	{
		pDoc->SetModifiedFlag(TRUE);
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		AfxMessageBox(L"分配内存失败！系统提示");// 警告
	}

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCTemplateView::Onsobel()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lWidth;      //图象的宽度和高度
	long	lHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpDIB;		//指向源图象的指针，指向信息头
	LPSTR	lpDIBBits;	//指向源像素的指针，指向位图数据
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpDIB) return;
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);			// 找到DIB图象像素起始位置	
	lWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * lpSrcBitCount);		// 计算图象每行的字节数

	// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;
	//循环变量
	long i;
	long j;
	int		TempHeight;
	int		TempWidth;
	FLOAT	fTempC;
	int		TempX;
	int		TempY;
	FLOAT aTemplate[9];
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);
	lpNewDIBBits1 = (char*)LocalLock(hNewDIBBits1);
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);
	lpNewDIBBits2 = (char*)LocalLock(hNewDIBBits2);
	lpDst1 = (char*)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char*)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// 设置Sobel模板参数
	TempWidth = 3;
	TempHeight = 3;
	fTempC = 1.0;
	TempX = 1;
	TempY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -2.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 2.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	Template(lpNewDIBBits1, lWidth, lHeight,
		TempHeight, TempWidth, TempX, TempY, aTemplate, fTempC);

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	Template(lpNewDIBBits2, lWidth, lHeight,
		TempHeight, TempWidth, TempX, TempY, aTemplate, fTempC);

	//求两幅缓存图像的最大值
	for (j = 0; j < lHeight; j++)
	{
		for (i = 0; i < lWidth - 1; i++)
		{

			// 指向缓存图像1倒数第j行，第i个像素的指针			
			lpDst1 = (char*)lpNewDIBBits1 + lWidth * j + i;

			// 指向缓存图像2倒数第j行，第i个像素的指针			
			lpDst2 = (char*)lpNewDIBBits2 + lWidth * j + i;

			if (*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;

		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);


	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCTemplateView::Onrobert()
{
	CMFCTemplateDoc* pDoc = GetDocument();
	// 指向DIB的指针
	LPSTR	lpDIB;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	long lWidth, lHeight;
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	// 更改光标形状
	BeginWaitCursor();
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lWidth = pDoc->m_dib.GetWidth(lpDIB);	// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpDIB);	// 获取图象的高度	

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;

	//像素值
	double result;
	unsigned char pixel[4];

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	//使用水平方向的结构元素进行腐蚀
	for (j = lHeight - 1; j > 0; j--)
	{
		for (i = 0; i < lWidth - 1; i++)
		{
			//使用2×2的模板，为防止越界,不处理
			//最下边和最右边的两列像素

			// 指向源图像第j行，第i个象素的指针			
			lpSrc = (char*)lpDIBBits + lWidth * j + i;

			// 指向目标图像第j行，第i个象素的指针			
			lpDst = (char*)lpNewDIBBits + lWidth * j + i;
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			result = sqrt((pixel[0] - pixel[3]) * (pixel[0] - pixel[3]) + \
				(pixel[1] - pixel[2]) * (pixel[1] - pixel[2]));
			*lpDst = (unsigned char)result;

		}
	}

	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}

//二值化
void CMFCTemplateView::Onerzhi()
{
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	LPSTR    lpDIB;// 指向DIB的指针

	// 由DIB句柄得到DIB指针并锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	LPSTR   lpDIBBits;
	BYTE* lpSrc;
	LONG    lWidth;
	LONG      lHeight;
	LONG    lLineBytes;
	int     lpSrcBitCount;
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);
	lWidth = pDoc->m_dib.GetWidth(lpDIB);
	lHeight = pDoc->m_dib.GetHeight(lpDIB);
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * lpSrcBitCount);
	int i, j;

	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			//lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			if (*lpSrc > 128)
				*lpSrc = 255;
			//否则设置为0，即黑点
			else *lpSrc = 0;

		}
	}
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}



#include "CDlgErosion.h"
void CMFCTemplateView::Onxingtai()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	// 指向DIB的指针
	LPSTR	lpDIB;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	int nMode1;
	int nMode2;
	// 创建对话框
	CDlgErosion dlgPara;
	// 初始化变量值
	dlgPara.m_nMode1 = 0;
	dlgPara.m_nMode2 = 0;
	// 显示对话框，提示用户设定腐蚀方向
	if (dlgPara.DoModal() != IDOK)
	{
		// 返回
		return;
	}
	// 获取用户设定的选择
	nMode1 = dlgPara.m_nMode1;
	// 获取用户设定的方向
	CString st1r;
	st1r.Format(_T("Mode1：%d"), nMode1);
	//MessageBox(st1r);
	//AfxMessageBox(L"mode1为" + 0);
	nMode2 = dlgPara.m_nMode2;
	CString str;
	str.Format(_T("Mode2：%d"), nMode2);
	//MessageBox(str);
	int structure[3][3];
	if (nMode2 == 2)
	{
		structure[0][0] = dlgPara.m_nstru1;
		structure[0][1] = dlgPara.m_nstru2;
		structure[0][2] = dlgPara.m_nstru3;
		structure[1][0] = dlgPara.m_nstru4;
		structure[1][1] = dlgPara.m_nstru5;
		structure[1][2] = dlgPara.m_nstru6;
		structure[2][0] = dlgPara.m_nstru7;
		structure[2][1] = dlgPara.m_nstru8;
		structure[2][2] = dlgPara.m_nstru9;
	}
	//如果是腐蚀运算
	if (nMode1 ==0) {
		// 删除对话框

		delete dlgPara;
		// 更改光标形状
		BeginWaitCursor();
		// 找到DIB图像象素起始位置
		lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
		int lHeight = pDoc->m_dib.GetWidth(lpDIB);
		int lWidth = pDoc->m_dib.GetWidth(lpDIB);
		//自定义腐蚀

	// 指向源图像的指针
		LPSTR	lpSrc;

		// 指向缓存图像的指针
		LPSTR	lpDst;

		// 指向缓存DIB图像的指针
		LPSTR	lpNewDIBBits;
		HLOCAL	hNewDIBBits;

		//循环变量
		long i;
		long j;
		int  n;
		int  m;

		//像素值
		unsigned char pixel;
		int flag=0;
		// 暂时分配内存，以保存新图像
		hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

		if (hNewDIBBits == NULL)
		{
			// 分配内存失败
			AfxMessageBox(L"WRONG-1");
		}

		// 锁定内存
		lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);


		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行腐蚀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者左右有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//AfxMessageBox(L"正在垂直腐蚀！");
			//使用垂直方向的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{

					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 2;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者上下有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{

						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}
			//AfxMessageBox(L"垂直腐蚀！");
		}
		else
		{
			//使用自定义的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 3;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
					//则将目标图像中的当前点赋成白色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 255)
							{
								*lpDst = (unsigned char)255;
								break;
							}
						}
					}

				}
			}
			//AfxMessageBox(L"自定义腐蚀！");
		}
		if (flag == 1) {
			AfxMessageBox(L"错误1");
		}
		else if (flag == 2) {
				AfxMessageBox(L"错误2");
		}
		else if (flag == 3) {
			AfxMessageBox(L"错误3");
		}
		// 复制腐蚀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
		AfxMessageBox(L"腐蚀完成！");
		// 释放内存
		LocalUnlock(hNewDIBBits);
		//LocalFree(hNewDIBBits);

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);




		// 调用ErosionDIB()函数腐蚀DIB
		/*
		if (ErosionDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		{
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		}*/
	}
	//如果是膨胀运算
	else if (nMode1 == 1) {
		// 删除对话框
		int flag = 0;
		delete dlgPara;
		// 更改光标形状
		BeginWaitCursor();
		// 找到DIB图像象素起始位置
		lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

		// 指向源图像的指针
		LPSTR	lpSrc;

		// 指向缓存图像的指针
		LPSTR	lpDst;

		// 指向缓存DIB图像的指针
		LPSTR	lpNewDIBBits;
		HLOCAL	hNewDIBBits;

		//循环变量
		long i;
		long j;
		int  n;
		int  m;

		//像素值
		unsigned char pixel;
		int lHeight = pDoc->m_dib.GetWidth(lpDIB);
		int lWidth = pDoc->m_dib.GetWidth(lpDIB);
		// 暂时分配内存，以保存新图像
		hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

		if (hNewDIBBits == NULL)
		{
			// 分配内存失败
			AfxMessageBox(L"失败");
		}

		// 锁定内存
		lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);


		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行膨胀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && pixel != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者左右只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 2;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者上下只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else
		{
			//使用自定义的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 3;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
					//则将目标图像中的当前点赋成黑色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 0)
							{
								*lpDst = (unsigned char)0;
								break;
							}
						}
					}

				}
			}

		}
		// 复制膨胀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
		if (flag == 1) {
			AfxMessageBox(L"错误1！目标图像中含有0和255外的其它灰度值");
		}
		else if (flag == 2) {
			AfxMessageBox(L"错误2！目标图像中含有0和255外的其它灰度值");
		}
		else if (flag == 3) {
			AfxMessageBox(L"错误3！目标图像中含有0和255外的其它灰度值");
		}
		// 释放内存
		LocalUnlock(hNewDIBBits);
		//LocalFree(hNewDIBBits);



		// 调用ErosionDIB()函数腐蚀DIB
		//if (DilationDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		//{
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		//}
	}
	//如果是开运算
	else if (nMode1 == 2) {
		// 删除对话框
		delete dlgPara;
		// 更改光标形状
		BeginWaitCursor();
		// 找到DIB图像象素起始位置
		lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

		LPSTR	lpSrc;

		// 指向缓存图像的指针
		LPSTR	lpDst;

		// 指向缓存DIB图像的指针
		LPSTR	lpNewDIBBits;
		HLOCAL	hNewDIBBits;
		int lHeight = pDoc->m_dib.GetWidth(lpDIB);
		int lWidth = pDoc->m_dib.GetWidth(lpDIB);
		//循环变量
		long i;
		long j;
		int  n;
		int  m;
		int flag = 0;
		//像素值
		unsigned char pixel;

		// 暂时分配内存，以保存新图像
		hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

		if (hNewDIBBits == NULL)
		{
			// 分配内存失败
			flag = 1;
		}

		// 锁定内存
		lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);


		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行腐蚀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者左右有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者上下有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}

		}
		else
		{
			//使用自定义的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
					//则将目标图像中的当前点赋成白色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 255)
							{
								*lpDst = (unsigned char)255;
								break;
							}
						}
					}

				}
			}

		}
		// 复制腐蚀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

		// 重新初始化新分配的内存，设定初始值为255
		//lpDst = (char *)lpNewDIBBits;
		//memset(lpDst, (BYTE)255, lWidth * lHeight);


		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行膨胀 E
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者左右只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者上下只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else
		{
			//使用自定义的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
					//则将目标图像中的当前点赋成黑色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 0)
							{
								*lpDst = (unsigned char)0;
								break;
							}
						}
					}

				}
			}

		}
		// 复制膨胀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// 调用ErosionDIB()函数腐蚀DIB
		//if (OpenDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		//{
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		//}
	}
	//如果是闭运算
	else if (nMode1 == 3) {
	int flag = 0;
	delete dlgPara;
	// 更改光标形状
	BeginWaitCursor();
	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向缓存图像的指针
	LPSTR	lpDst;

	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long i;
	long j;
	int  n;
	int  m;

	//像素值
	unsigned char pixel;
	int lHeight = pDoc->m_dib.GetWidth(lpDIB);
	int lWidth = pDoc->m_dib.GetWidth(lpDIB);
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		AfxMessageBox(L"失败");
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char*)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);
		
		// 调用ErosionDIB()函数腐蚀DIB
		//if (CloseDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		//{
		// 指向源图像的指针
		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行膨胀 E
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者左右只要有一个点是白色，则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//源图像中当前点自身或者上下只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 0)
						{
							*lpDst = (unsigned char)0;
							break;
						}
					}

				}
			}

		}
		else
		{
			//使用自定义的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)255;

					//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
					//则将目标图像中的当前点赋成黑色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 0)
							{
								*lpDst = (unsigned char)0;
								break;
							}
						}
					}

				}
			}

		}
		// 复制膨胀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
		if (flag == 1) {
			AfxMessageBox(L"错误1");
		}
		else if (flag == 2) {
			AfxMessageBox(L"错误2");
		}
		else if (flag == 3) {
			AfxMessageBox(L"错误3");
		}
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);


		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行腐蚀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者左右有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}

		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素

					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果源图像中当前点自身或者上下有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 255)
						{
							*lpDst = (unsigned char)255;
							break;
						}
					}

				}
			}

		}
		else
		{
			//使用自定义的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;

					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;

					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;

					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 1;

					//目标图像中的当前点先赋成黑色
					*lpDst = (unsigned char)0;

					//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
					//则将目标图像中的当前点赋成白色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 255)
							{
								*lpDst = (unsigned char)255;
								break;
							}
						}
					}

				}
			}

		}
		// 复制腐蚀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		//}

	}
	//外边界
	else if (nMode1 == 4) {

		// 删除对话框
		delete dlgPara;
		// 更改光标形状
		BeginWaitCursor();
		// 找到DIB图像象素起始位置
		lpDIBBits = pDoc->m_dib.GetBits(lpDIB);
		int flag = 0;
		// 指向源图像的指针
		LPSTR	lpSrc;
		// 指向缓存图像的指针
		LPSTR	lpDst;
		// 指向缓存DIB图像的指针
		LPSTR	lpNewDIBBits;
		HLOCAL	hNewDIBBits;
		//循环变量
		long i;
		long j;
		int  n;
		int  m;
		int lHeight = pDoc->m_dib.GetWidth(lpDIB);
		int lWidth = pDoc->m_dib.GetWidth(lpDIB);
		//像素值
		unsigned char pixel;
		// 暂时分配内存，以保存新图像
		hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
		if (hNewDIBBits == NULL)
		{
			// 分配内存失败
			flag = 11;
		}
		// 锁定内存
		lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);
		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行膨胀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && pixel != 0)
						flag = 1;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//源图像中当前点自身或者左右只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 255)
						{
							if ((unsigned char)*lpSrc == 0)
								*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 2;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//源图像中当前点自身或者上下只要有一个点是黑色，
					//则将目标图像中的当前点赋成黑色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 255)
						{
							if ((unsigned char)*lpSrc == 0)
								*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
		}
		else
		{
			//使用自定义的结构元素进行膨胀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag = 3;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
					//则将目标图像中的当前点赋成黑色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 255)
							{
								if ((unsigned char)*lpSrc == 0)
									*lpDst = (unsigned char)255;
								break;
							}
						}
					}
				}
			}
		}
		// 复制膨胀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
		if (flag == 1) {
			AfxMessageBox(L"错误1！目标图像中含有0和255外的其它灰度值");
		}
		else if (flag == 2) {
			AfxMessageBox(L"错误2！目标图像中含有0和255外的其它灰度值");
		}
		else if (flag == 3) {
			AfxMessageBox(L"错误3！目标图像中含有0和255外的其它灰度值");
		}
		else if (flag == 11) {
			AfxMessageBox(L"错误4！内存分配失败");
		}
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// 调用ErosionDIB()函数腐蚀DIB
		//if (CloseDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		//{
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		//}
	}
	//内边界
	else if (nMode1 == 5) {
		// 删除对话框
		delete dlgPara;
		// 更改光标形状
		BeginWaitCursor();
		// 找到DIB图像象素起始位置
		int flag = 0;
		int lHeight = pDoc->m_dib.GetWidth(lpDIB);
		int lWidth = pDoc->m_dib.GetWidth(lpDIB);
		lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

		// 指向源图像的指针
		LPSTR	lpSrc;
		// 指向缓存图像的指针
		LPSTR	lpDst;
		// 指向缓存DIB图像的指针
		LPSTR	lpNewDIBBits;
		HLOCAL	hNewDIBBits;
		//循环变量
		long i;
		long j;
		int  n;
		int  m;
		//像素值
		unsigned char pixel;
		// 暂时分配内存，以保存新图像
		hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);
		if (hNewDIBBits == NULL)
		{
			// 分配内存失败
			flag=1;
		}
		// 锁定内存
		lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
		// 初始化新分配的内存，设定初始值为255
		lpDst = (char*)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);
		if (nMode2 == 0)
		{
			//使用水平方向的结构元素进行腐蚀
			for (j = 0; j < lHeight; j++)
			{
				for (i = 1; i < lWidth - 1; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag=1;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//如果源图像中当前点自身或者左右有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + n - 1);
						if (pixel == 0)
						{
							if ((unsigned char)*lpSrc == 255)
								*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
		}
		else if (nMode2 == 1)
		{
			//使用垂直方向的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用1×3的结构元素，为防止越界，所以不处理最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag=1;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//如果源图像中当前点自身或者上下有一个点不是黑色，
					//则将目标图像中的当前点赋成白色
					for (n = 0; n < 3; n++)
					{
						pixel = *(lpSrc + (n - 1) * lWidth);
						if (pixel == 0)
						{
							if ((unsigned char)*lpSrc == 255)
								*lpDst = (unsigned char)255;
							break;
						}
					}
				}
			}
		}
		else
		{
			//使用自定义的结构元素进行腐蚀
			for (j = 1; j < lHeight - 1; j++)
			{
				for (i = 0; i < lWidth; i++)
				{
					//由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边的两列像素
					//和最上边和最下边的两列像素
					// 指向源图像倒数第j行，第i个象素的指针			
					lpSrc = (char*)lpDIBBits + lWidth * j + i;
					// 指向目标图像倒数第j行，第i个象素的指针			
					lpDst = (char*)lpNewDIBBits + lWidth * j + i;
					//取得当前指针处的像素值，注意要转换为unsigned char型
					pixel = (unsigned char)*lpSrc;
					//目标图像中含有0和255外的其它灰度值
					if (pixel != 255 && *lpSrc != 0)
						flag=1;
					//目标图像中的当前点先赋成白色
					*lpDst = (unsigned char)0;
					//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
					//则将目标图像中的当前点赋成白色
					//注意在DIB图像中内容是上下倒置的
					for (m = 0; m < 3; m++)
					{
						for (n = 0; n < 3; n++)
						{
							if (structure[m][n] == -1)
								continue;
							pixel = *(lpSrc + ((2 - m) - 1) * lWidth + (n - 1));
							if (pixel == 0)
							{
								if ((unsigned char)*lpSrc == 255)
									*lpDst = (unsigned char)255;
								break;
							}
						}
					}
				}
			}
		}
		// 复制腐蚀后的图像
		memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);
		// 释放内存
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);

		// 调用ErosionDIB()函数腐蚀DIB
		//if (CloseDIB(lpDIBBits, pDoc->m_dib.GetWidth(lpDIB) * 8, pDoc->m_dib.GetHeight(lpDIB), nMode2, structure))
		//{
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		//}
	}
	else
	{
	// 提示用户
	AfxMessageBox(L"失败！");
	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}

int WINAPI CMFCTemplateView::ThresholdDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,LONG lLineBytes)
{

	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i;
	long j;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, NewThreshold, MaxGray, MinGray, iMean1GrayValue, iMean2GrayValue;

	//用于计算区域灰度平均值的中间变量
	long p1, p2, s1, s2;

	//迭代次数
	int DiedaiNumber;


	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}

	//获得直方图
	MaxGray = 0;
	MinGray = 255;
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
		
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
			pixel = (unsigned char)*lpSrc;
			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (MinGray > pixel)
			{
				MinGray = pixel;
			}
			if (MaxGray < pixel)
			{
				MaxGray = pixel;
			}
		}
	}

	//迭代求最佳阈值
	NewThreshold = (MinGray + MaxGray) / 2;
	iThreshold = 0;

	for (DiedaiNumber = 0; iThreshold != NewThreshold && DiedaiNumber < 100; DiedaiNumber++)
	{
		iThreshold = NewThreshold;
		//用于计算区域灰度平均值的中间变量
		p1 = 0;p2 = 0;s1 = 0;s2 = 0;
		//求两个区域的灰度平均值
		for (i = MinGray; i < iThreshold; i++)
		{
			p1 += lHistogram[i] * i;
			s1 += lHistogram[i];
		}
		if (s1 == 0) continue;
		iMean1GrayValue = (unsigned char)(p1 / s1);
		for (i = iThreshold + 1; i < MaxGray; i++)
		{
			p2 += lHistogram[i] * i;
			s2 += lHistogram[i];
		}
		if (s2 == 0) continue;
		iMean2GrayValue = (unsigned char)(p2 / s2);
		NewThreshold = (iMean1GrayValue + iMean2GrayValue) / 2;
	}

	return iThreshold;
}

int WINAPI CMFCTemplateView::OTSUDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,LONG lLineBytes)
{
	// 指向源图像的指针
	LPSTR	lpSrc;

	//循环变量
	long i, j, k;
	//用于计算区域灰度平均值的中间变量
	long p1, p2, s1, s2;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold, NewThreshold, MaxGray, MinGray, iMean1GrayValue, iMean2GrayValue;

	//前景点数占图像比例，背景点数占图像比例
	double w0, w1;
	//方差
	double G = 0, tempG = 0;


	for (i = 0; i < 256; i++)
	{
		lHistogram[i] = 0;
	}
	//获得直方图
	MaxGray = 0;
	MinGray = 255;
	for (i = 0; i < lWidth; i++)
	{
		for (j = 0; j < lHeight; j++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;

			lHistogram[pixel]++;
			//修改最大，最小灰度值
			if (MinGray > pixel)
			{
				MinGray = pixel;
			}
			if (MaxGray < pixel)
			{
				MaxGray = pixel;
			}
		}
	}

	for (k = MinGray; k < MaxGray; k++)
	{
		NewThreshold = k;
		p1 = 0;p2 = 0;s1 = 0;s2 = 0;
		//求两个区域的灰度平均值
		for (i = MinGray; i <= NewThreshold; i++)
		{
			p1 += lHistogram[i] * i;
			s1 += lHistogram[i];
		}

		iMean1GrayValue = (unsigned char)(p1 / s1);
		w0 = (double)(s1) / (lWidth * lHeight);

		for (i = NewThreshold + 1; i <= MaxGray; i++)
		{
			p2 += lHistogram[i] * i;
			s2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(p2 / s2);
		w1 = 1 - w0;

		G = (double)w0 * w1 * (iMean1GrayValue - iMean2GrayValue) * (iMean1GrayValue - iMean2GrayValue);
		if (G > tempG)
		{
			tempG = G;
			iThreshold = NewThreshold;
		}
	}
	return iThreshold;
}

void CMFCTemplateView::RegionSegAdaptive(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,LONG lLineBytes) {

	int y, x;

	int nThd[2][2]={0};
	int Location;
	//左上
	Location = 0;
	for (y = 0; y < lHeight / 2; y++)
		for (x = 0; x < lWidth / 2; x++) {
			Location += lpDIBBits[y*lLineBytes + x];
		}
	Location /= ((lHeight / 2)*(lWidth / 2));
	nThd[0][0] = Location;

	for (y = 0; y < lHeight / 2; y++)
		for (x = 0; x < lWidth / 2; x++) {
			if (lpDIBBits[y*lLineBytes + x] < nThd[0][0])
				lpDIBBits[y*lLineBytes + x] = 255;
			else
				lpDIBBits[y*lLineBytes + x] = 0;
		}
	//左下
	Location = 0;
	for (y = lHeight / 2; y < lHeight; y++)
		for (x = 0; x < lWidth / 2; x++) {
			Location += lpDIBBits[y*lLineBytes + x];
		}
	Location /= ((lHeight - lHeight / 2)*(lWidth / 2));
	nThd[1][0] = Location;

	for (y = lHeight / 2; y < lHeight; y++)
		for (x = 0; x < lWidth / 2; x++) {
			if (lpDIBBits[y*lLineBytes + x] < nThd[1][0])
				lpDIBBits[y*lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y*lLineBytes + x] = (unsigned char)0;
		}
	//右上
	Location = 0;
	for (y = 0; y < lHeight / 2; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			Location += lpDIBBits[y*lLineBytes + x];
		}
	Location /= ((lHeight / 2)*(lWidth - lWidth / 2));
	nThd[0][1] = Location;

	for (y = 0; y < lHeight / 2; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			if (lpDIBBits[y*lLineBytes + x] < nThd[0][1])
				lpDIBBits[y*lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y*lLineBytes + x] = (unsigned char)0;
		}
	//右下
	Location = 0;
	for (y = lHeight / 2; y < lHeight; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			Location += lpDIBBits[y*lLineBytes + x];
		}
	Location /= ((lHeight - lHeight / 2)*(lWidth - lWidth / 2));
	nThd[1][1] = Location;

	for (y = lHeight / 2; y < lHeight; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			if (lpDIBBits[y*lLineBytes + x] < nThd[1][1])
				lpDIBBits[y*lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y*lLineBytes + x] = (unsigned char)0;
		}
	for (y = 0; y < lHeight; y++)
		for (x = 0; x < lWidth; x++) {
			lpDIBBits[y*lLineBytes + x] = 255 - lpDIBBits[y*lLineBytes + x];
		}
}

//双峰法,要求图像的直方图是双峰的
int WINAPI CMFCTemplateView::DF(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int bitcount) {
	typedef struct Df
	{
		int grey;
		int num;
	}Df;
	unsigned char* p;
	int His[256];
	//统计直方图
	int lLineBytes = ((lWidth * bitcount) + 31) / 32 * 4;
	for (int x = lHeight - 1; x >= 0; x--)//图像由上到下
	{
		for (int y = 0; y < lWidth; y++)//从左向右
		{
			p = (unsigned char*)lpDIBBits + lLineBytes * x + y;
			int num = *p;
			His[num]++;
		}
	}

	Df Dfs[256];//用于统计波峰
	int cnt = 0;//计数
	Dfs[cnt].grey = 0;//Dfs[i]的灰度值，先存0
	Dfs[cnt].num = His[0];//Dfs[i]的统计数
	cnt++;//cnt=1
	for (int i = 1; i < 255; i++)
	{
		if (His[i] > His[i + 1] && His[i] > His[i - 1])
		{
			//波峰
			Dfs[cnt].grey = i;
			Dfs[cnt].num = His[i];
			cnt++;
		}
	}
	Dfs[cnt].grey = 255;
	Dfs[cnt].num = His[255];
	cnt++;//波峰数
	Df max = Dfs[0], snd = Dfs[0];//寻找最大和第二大的波峰
	for (int i = 0; i < cnt; i++)
	{
		if (Dfs[i].num > max.num)
		{
			snd = max;
			max = Dfs[i];
		}
		else if (Dfs[i].num > snd.num)
		{
			snd = Dfs[i];
		}
	}

	int i = (max.grey > snd.grey ? snd.grey : max.grey);//从小的开始
	int mnum = (max.grey > snd.grey ? max.grey : snd.grey);
	Df K = max;
	for (; i < mnum; i++)//找两个波峰之间的波谷
	{
		if (His[i] < K.num)
		{
			K.num = His[i];
			K.grey = i;
		}
	}
	//波谷的灰度值(阈值)为 K.grey	
	return K.grey;
}
/*
阈值
*/
#include "yuzhi.h"
void CMFCTemplateView::Onyuzhi()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument(); 	
	int  lSrcLineBytes;		//图象每行的字节数
	int	 lSrcHeight;      //图象的宽度和高度
	int	  lSrcWidth;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	LONG lLineBytes;//每行
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);// 获取图象的高度		
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图象每行的字节数
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);//图像像素
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);

	Yuzhifenge dlgPara1;//创建对话框
	int i, j;
	dlgPara1.pDoc = pDoc;
	dlgPara1.lpSrcDib= lpSrcDib;
	dlgPara1.temp3 = 256;
	dlgPara1.lpSrcBitCount = lpSrcBitCount;
	dlgPara1.lpSrcStartBits = lpSrcStartBits;
	dlgPara1.lSrcHeight = lSrcHeight;
	dlgPara1.lSrcWidth = lSrcWidth;
	dlgPara1.lSrcLineBytes = lSrcLineBytes;
	//把初始图像拷贝给对话框函数
	dlgPara1.StartBits = new unsigned char[lSrcHeight * lSrcWidth * sizeof(unsigned char)];
	memcpy(dlgPara1.StartBits, lpSrcStartBits, lSrcHeight * lSrcWidth * sizeof(unsigned char));
	dlgPara1.temp1 = ThresholdDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, lLineBytes);
	dlgPara1.temp2 = OTSUDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, lLineBytes);
	dlgPara1.temp4 = DF(lpSrcStartBits, lSrcWidth, lSrcHeight, lpSrcBitCount);
	if (dlgPara1.DoModal() != IDOK)//显示对话框，设定平移量
	{
		return;
	}
	int threshold = dlgPara1.m_threshold;
	if (threshold != 256)
	{
		for (i = 0; i < lSrcHeight; i++) {
			for (j = 0; j < lSrcWidth; j++) {
				lpSrcDib = (char*)lpSrcStartBits + lSrcLineBytes * i + j;
				if ((unsigned char)*lpSrcDib > threshold)
					(*lpSrcDib) = 255;
				else
					(*lpSrcDib) = 0;
			}
		}
	}
	else if (threshold ==256)
	{
		//dlgPara1.m_threshold = temp3;
		RegionSegAdaptive(lpSrcStartBits, lSrcWidth, lSrcHeight,lLineBytes);
	
	}
	
	delete dlgPara1;
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

#include "chuangkou.h"
void CMFCTemplateView::Onwinchange()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	int  lSrcLineBytes;		//图象每行的字节数
	int	 lSrcHeight;      //图象的宽度和高度
	int	  lSrcWidth;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);// 获取图象的高度		
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图象每行的字节数
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);//图像像素


	Windowchange dlgPara1;//创建对话框

	dlgPara1.pDoc = pDoc;
	dlgPara1.lpSrcDib = lpSrcDib;
	dlgPara1.lpSrcBitCount = lpSrcBitCount;
	dlgPara1.lpSrcStartBits = lpSrcStartBits;
	dlgPara1.lSrcHeight = lSrcHeight;
	dlgPara1.lSrcWidth = lSrcWidth;
	dlgPara1.lSrcLineBytes = lSrcLineBytes;
	//把初始图像拷贝给对话框函数
	dlgPara1.StartBits = new unsigned char[lSrcHeight * lSrcWidth * sizeof(unsigned char)];
	memcpy(dlgPara1.StartBits, lpSrcStartBits, lSrcHeight * lSrcWidth * sizeof(unsigned char));


	int i, j;
	if (dlgPara1.DoModal() != IDOK)//显示对话框，设定平移量
	{
		return;
	}
	int up = dlgPara1.m_bUp;
	int down = dlgPara1.m_bLow;



	delete dlgPara1;

	for (i = 0; i < lSrcHeight; i++) {
		for (j = 0; j < lSrcWidth; j++) {
			lpSrcDib = (char*)lpSrcStartBits + lSrcLineBytes * i + j;
			if ((unsigned char)*lpSrcDib > up)
				(*lpSrcDib) = 255;
			if ((unsigned char)*lpSrcDib < down)
				(*lpSrcDib) = 0;
		}
	}

	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


BOOL WINAPI CMFCTemplateView::GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{
	unsigned char* lpSrc;
	LONG	i;
	LONG	j;
	BYTE	bMap[256];
	for (i = 0; i <= bX1; i++)
	{
		if (bX1 > 0)
		{
			bMap[i] = (BYTE)(bY1 * i / bX1);
		}
		else
		{
			bMap[i] = 0;
		}
	}

	for (; i <= bX2; i++)
	{
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE)((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}

	for (; i < 256; i++)
	{
		if (bX2 != 255)
		{
			bMap[i] = bY2 + (BYTE)((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			bMap[i] = 255;
		}
	}
	for (i = 0; i < lHeight; i++)
	{

		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			*lpSrc = bMap[*lpSrc];

		}

	}

	return TRUE;

}

//灰度拉伸
#include "Lashen.h"
void CMFCTemplateView::OnLashen()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	LPSTR	lpDIB;

	int	lpDIBct;
	// 指向DIB象素指针
	LPSTR   lpDIBBits;
	// 创建对话框
	Lashen  dlgPara1;
	dlgPara1.pDoc = GetDocument();
	// 点1坐标
	BYTE	bX1;
	BYTE	bY1;
	// 点2坐标
	BYTE	bX2;
	BYTE	bY2;
	// 锁定DIB

	// 找到DIB图像象素起始位置
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素
	lpDIBct= pDoc->m_dib.GetBitCount(lpDIB);//图像像素
	int lWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lHeight = pDoc->m_dib.GetHeight(lpDIB);// 获取图象的高度		
	int lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * 8);
	


	dlgPara1.m_1x = 50;
	dlgPara1.m_1y = 30;
	dlgPara1.m_2x = 200;
	dlgPara1.m_2y = 220;

	dlgPara1.lpSrcDib = lpDIB;
	dlgPara1.lpSrcBitCount = lpDIBct;
	dlgPara1.lpSrcStartBits = lpDIBBits;
	dlgPara1.lSrcHeight = lHeight;
	dlgPara1.lSrcWidth = lWidth;
	dlgPara1.lSrcLineBytes = lLineBytes;

	//把初始图像拷贝给对话框函数
	dlgPara1.StartBits = new unsigned char[lHeight * lWidth * sizeof(unsigned char)];
	memcpy(dlgPara1.StartBits, lpDIBBits, lHeight * lWidth * sizeof(unsigned char));
	// 显示对话框，提示用户设定拉伸位置	
	if (dlgPara1.DoModal() != IDOK)
	{
		return;
	}
	// 获取用户的设定
	bX1 = dlgPara1.m_1x;
	bY1 = dlgPara1.m_1y;
	bX2 = dlgPara1.m_2x;
	bY2 = dlgPara1.m_2y;


	


	// 更改光标形状
	BeginWaitCursor();

delete dlgPara1;

	// 调用GrayStretch()函数进行灰度拉伸
	GrayStretch(lpDIBBits, lWidth, lHeight, lLineBytes, bX1, bY1, bX2, bY2);
	// 删除对话框
	
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	// 恢复光标
	EndWaitCursor();
}


BOOL WINAPI Junheng(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int lLineBytes)
{
	unsigned char* lpSrc;
	LONG	lTemp;
	LONG	i;
	LONG	j;
	BYTE	bMap[256];
	// 灰度映射表
	LONG	lCount[256];
	// 图像每行的字节数
	// 计算图像每行的字节数
	for (i = 0; i < 256; i++)
	{
		lCount[i] = 0;
	}
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * i + j;
			// 计数加1
			int b = (int)(*lpSrc);
			lCount[b]++;
		}
	}
	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		lTemp = 0;
		for (j = 0; j <= i; j++)
		{
			lTemp += lCount[j];
		}
		// 计算对应的新灰度值
		bMap[i] = (BYTE)(lTemp * 255 / lHeight / lWidth);
	}
	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	// 返回
	return TRUE;
}
void CMFCTemplateView::Onjunheng()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	LPSTR	lpDIB;
	LPSTR   lpDIBBits;
	// 找到DIB图像象素起始位置
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);//图像像素
	int lWidth = pDoc->m_dib.GetWidth(lpDIB);
	int lHeight = pDoc->m_dib.GetHeight(lpDIB);// 获取图象的高度		
	int lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * 8);

	BeginWaitCursor();
	Junheng(lpDIBBits, lWidth, lHeight, lLineBytes);


	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定



	// 恢复光标

	EndWaitCursor();
}

#include "Move.h"
void CMFCTemplateView::OnMove()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档
	long    lLineBytes;		//图象每行的字节数
	long	lWidth;      //图象的宽度和高度
	long	lHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpDib;		//指向源图象的指针	
	LPSTR	lpDIBBits;	//指向源像素的指针
	lpDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpDib) return;
	if (pDoc->m_dib.GetColorNum(lpDib) != 256)// 判断是否是8-bpp位图
	{
		AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回	
	lpDIBBits = pDoc->m_dib.GetBits(lpDib);			// 找到DIB图象像素起始位置	
	lWidth = pDoc->m_dib.GetWidth(lpDib);					// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpDib);					// 获取图象的高度
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDib);                    //获取图像位深
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * 8);		// 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	Move dlgPara;// 创建对话框	

	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}

	long MoveX = dlgPara.MoveX;
	long MoveY = dlgPara.MoveY;

	// 指向源图像的指针
	LPSTR	lpSrc;

	// 指向要复制区域的指针
	LPSTR	lpDst;

	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	LONG	i;
	LONG	j;

	LONG	x;
	LONG	y;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		//return FALSE;
		AfxMessageBox(L"分配内存失败");// 警告				
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定		
		return;									//返回
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	for (i = 0; i < lHeight; i++)
	{
		for (j = 0; j < lWidth; j++)
		{
			// 由于DIB中图像第一行其实保存在最后一行的位置，因此lpDst值不是(char *)lpNewDIBBits + lLineBytes * i + j，而是(char *)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j
			lpDst = (char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			// 计算该象素在源DIB中的坐标
			x = i - MoveX;
			y = j - MoveY;

			// 判断是否在源图范围内
			if ((y >= 0) && (y < lWidth) && (x >= 0) && (x < lHeight))
			{
				// 指向源DIB第i0行，第j0个象素的指针
				// 同样要注意DIB上下倒置的问题
				lpSrc = (char*)lpDIBBits + lLineBytes * (lHeight - 1 - x) + y;
				*lpDst = *lpSrc;
			}
			else
			{
				// 对于源图中没有的象素，直接赋值为255
				*((unsigned char*)lpDst) = 255;
			}

		}
	}

	// 复制平移后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

#include "Revolve.h"


//图像旋转
void CMFCTemplateView::OnRevolve()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;   //指向DIB的指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());   //锁定DIB
	int iRotateAngle;
	//获取设定的旋转角度
	Revolve dlg1;
	begin:
	//创建新DIB
	//AfxMessageBox(iRotateAngle);
	if (dlg1.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}

	HDIB hNewDIB = NULL;
	//更改光标形状
	BeginWaitCursor();
	iRotateAngle = dlg1.dushu;
	if (dlg1.dushu < 0 || dlg1.dushu>360) {
		AfxMessageBox(L"对不起，输入角度须在0-360°范围内！");
		goto begin;
	}
	/*
	CString strInfo;
	strInfo.Format(_T("%d"), iRotateAngle);
	MessageBox(0, strInfo, NULL);*/
	//调用RotateDIB()函数旋转DIB
	hNewDIB = (HDIB)::RotateDIB(lpDIB, iRotateAngle);

	//判断旋转是否成功
	if (hNewDIB != NULL)
	{
		//替换DIB，同时释放旧DIB对象
		pDoc->ReplaceHDIB(hNewDIB);

		//设置修改标记
		pDoc->SetModifiedFlag(TRUE);

		//更新视图
		pDoc->UpdateAllViews(NULL);

	}
	else
	{
		//提示用户
		AfxMessageBox(L"对不起，不是256色位图！");
	}
	// 删除对话框
	delete dlg1;
	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//恢复光标
	EndWaitCursor();
}

//水平镜像翻转
void CMFCTemplateView::OnMirrortrans()
{
	unsigned char* lpSrc;
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档
	LPSTR lpDIB;   //指向DIB的指针
	lpDIB = (LPSTR)::GlobalLock((HGLOBAL)pDoc->GetHObject());   //锁定DIB

	LPSTR lpDIBNew= lpDIB;   //指向DIB的指针
	
	long    lLineBytes;		//图象每行的字节数
	long	lWidth;      //图象的宽度和高度
	long	lHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpDIBBits;	//指向源像素的指针
	lWidth = pDoc->m_dib.GetWidth(lpDIB);					// 获取图象的宽度		
	lHeight = pDoc->m_dib.GetHeight(lpDIB);					// 获取图象的高度
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpDIB);                    //获取图像位深
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lWidth * 8);		// 计算图象每行的字节数

	BeginWaitCursor();
	
	int dataSizePerLineNew = (lWidth * 8 / 8 + 3) / 4 * 4;
	lpSrc = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeight];//用来存储新的位图
																										  //初始化
	memset(lpSrc, 200, sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeight);

	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;

	BITMAPINFOHEADER* pHead;//新建的一个指向位图信息头类型变量的指针
	RGBQUAD* pColorTable;//新建的一个指向颜色表类型变量的指针

	memcpy(lpSrc, lpDIB, sizeof(BITMAPINFOHEADER) + 256 * 4);

	int offset = sizeof(BITMAPINFOHEADER) + 256 * 4;

	LPSTR lpSrcStartBits = lpDIB + offset;
	unsigned char* lpSrcStartBitsNew = lpSrc + offset;




	for (int r = 0; r < lHeight; r++)
	{
		for (int c = 0; c < lWidth; c++)
		{
			int rNew = r;
			int cNew = lWidth - 1 - c;
			if (rNew < lHeight && rNew >= 0 && cNew >= 0 && cNew < lWidth)
			{
				unsigned char* pixel;
				pixel = (unsigned char*)lpSrcStartBits + r * dataSizePerLine + c;
				*(lpSrcStartBitsNew + rNew * dataSizePerLineNew + cNew) = *pixel;
			}
		}
	}

	memcpy(lpDIB, lpSrc, sizeof(BITMAPINFOHEADER) + 256 * 4 + dataSizePerLineNew * lHeight);

	//设置修改标记
	pDoc->SetModifiedFlag(TRUE);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	//恢复光标
	EndWaitCursor();
}


//滤镜
#include "Lvjing.h"

BOOL WINAPI MTemplate(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* Arr, FLOAT fCoef, float threshold)
{
	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// 计算结果
	FLOAT	fResult;

	// 图像每行的字节数
	LONG lLineBytes;

	// 计算图像每行的字节数
	lLineBytes = (lWidth + 3) / 4 * 4;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);

	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);

	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;
					// 保存象素值
					fResult += (*lpSrc) * Arr[k * iTempW + l];
				}
			}


			// 乘上系数
			fResult *= fCoef;

			fResult += threshold;

			//取绝对值
			fResult = (FLOAT)fabs(fResult);


			// 判断是否超过255
			if (fResult > 255)
			{
				// 直接赋g值为255
				*lpDst = 255;
			}
			else
			{
				// 赋值
				*lpDst = (unsigned char)(fResult + 0.5);
			}
		}
	}
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;

}


void CMFCTemplateView::OnLvj()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long  lSrcLineBytes;		//图象每行的字节数
	long	  lSrcWidth;      //图象的宽度和高度
	long	  lSrcHeight;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bpp位图
	//{		
		//AfxMessageBox(L"对不起，不是256色位图！");// 警告				
		  // ::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定		
		//return;									//返回
	 //}										//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数


	FLOAT operator1;
	FLOAT operator2;
	FLOAT operator3;
	FLOAT operator4;
	FLOAT operator5;
	FLOAT operator6;
	FLOAT operator7;
	FLOAT operator8;
	FLOAT operator9;

	int edge_direction = 0;

	int constant;
	double coefficient;



	// 创建对话框
	Lvjing dlgPara;
	unsigned char* lpSrcData = 0;
	//给Filter.cpp传值
	dlgPara.pDoc = pDoc;
	dlgPara.lpSrcBitCount = lpSrcBitCount;//////////////////////
	dlgPara.lpSrcStartBits = lpSrcStartBits;/////////////////
	dlgPara.lSrcHeight = lSrcHeight;///////////////////////////
	dlgPara.lSrcWidth = lSrcWidth;///////////////////////////
	dlgPara.lSrcLineBytes = lSrcLineBytes;///////////////////
	dlgPara.beginBits = new unsigned char[lSrcHeight * lSrcWidth * sizeof(unsigned char)];
	memcpy(dlgPara.beginBits, lpSrcStartBits, lSrcHeight * lSrcWidth * sizeof(unsigned char));

	if (lpSrcBitCount == 8) {
		// 初始化变量值

		// 显示对话框
		if (dlgPara.DoModal() != IDOK)
		{
			// 返回
			return;
		}


		// 获取用户设定

		operator1 = dlgPara.m_operator1;
		operator2 = dlgPara.m_operator2;
		operator3 = dlgPara.m_operator3;
		operator4 = dlgPara.m_operator4;
		operator5 = dlgPara.m_operator5;
		operator6 = dlgPara.m_operator6;
		operator7 = dlgPara.m_operator7;
		operator8 = dlgPara.m_operator8;
		operator9 = dlgPara.m_operator9;

		coefficient = dlgPara.m_coefficient;
		constant = dlgPara.m_constant;
		//CString strInfo;
		//strInfo.Format(_T("%d"), constant);
		//MessageBox(0, strInfo, NULL);
		//模板高度
		int iTempH;
		//模板宽度
		int iTempW;
		//模板系数
		//FLOAT fTempC;
		//模板中心元素X坐标
		int iTempMX;
		//模板中心元素Y坐标
		int iTempMY;
		//模板元素数组
		FLOAT aValue[9];



		// 设定平移量（3*3）
		iTempH = 3;
		iTempW = 3;
		iTempMX = 1;
		iTempMY = 1;
		//fTempC  = coefficient;//系数  	


		aValue[0] = operator1;
		aValue[1] = operator2;
		aValue[2] = operator3;
		aValue[3] = operator4;
		aValue[4] = operator5;
		aValue[5] = operator6;
		aValue[6] = operator7;
		aValue[7] = operator8;
		aValue[8] = operator9;

		// 删除对话框
		delete dlgPara;
		//CString strInfo;

		//AfxMessageBox(aValue[0]);
		// 更改光标形状
		BeginWaitCursor();
		if (coefficient == 99.9) {
			int page = 1;
			if (lpSrcBitCount == 24) page = 3;
			if (lpSrcBitCount == 8) page = 1;
			int changing = constant;
			//std::cout << changing;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					for (int l = 0; l < page; l++) {
						lpSrcData = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * page + l;
						int temp = *lpSrcData + changing;
						if (temp < 0) {
							*lpSrcData = 0;
						}
						else if (temp > 255) {
							*lpSrcData = 255;
						}
						else {
							*lpSrcData = (unsigned char)(temp + 0.5);
						}
					}

				}
			}
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		}
		else {

			if (MTemplate(lpSrcStartBits, lSrcWidth, lSrcHeight,
				iTempH, iTempW, iTempMX, iTempMY, aValue, coefficient, constant))
			{
				// 设置脏标记
				pDoc->SetModifiedFlag(TRUE);
				// 更新视图
				pDoc->UpdateAllViews(NULL);
			}
			else
			{
				// 提示用户
				//MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
				AfxMessageBox(L"分配内存失败！系统提示");// 警告
			}

		}

		// 恢复光标
		EndWaitCursor();
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	}

	//////////////////////////////////////////////////////////////
	if (lpSrcBitCount == 24) {
		// 初始化变量值
		
		// 显示对话框
		if (dlgPara.DoModal() != IDOK)
		{
			// 返回
			return;
		}
		// 获取用户设定

		operator1 = dlgPara.m_operator1;
		operator2 = dlgPara.m_operator2;
		operator3 = dlgPara.m_operator3;
		operator4 = dlgPara.m_operator4;
		operator5 = dlgPara.m_operator5;
		operator6 = dlgPara.m_operator6;
		operator7 = dlgPara.m_operator7;
		operator8 = dlgPara.m_operator8;
		operator9 = dlgPara.m_operator9;

		coefficient = dlgPara.m_coefficient;
		constant = dlgPara.m_constant;

		//模板高度
		int iTempH;
		//模板宽度
		int iTempW;
		//模板系数
		//FLOAT fTempC;
		//模板中心元素X坐标
		int iTempMX;
		//模板中心元素Y坐标
		int iTempMY;
		//模板元素数组
		FLOAT aValue[9];



		// 设定平移量（3*3）
		iTempH = 3;
		iTempW = 3;
		iTempMX = 1;
		iTempMY = 1;
		//fTempC  = coefficient;//系数  	
		aValue[0] = operator1;
		aValue[1] = operator2;
		aValue[2] = operator3;
		aValue[3] = operator4;
		aValue[4] = operator5;
		aValue[5] = operator6;
		aValue[6] = operator7;
		aValue[7] = operator8;
		aValue[8] = operator9;

		// 删除对话框
		delete dlgPara;
		//CString strInfo;
		//strInfo.Format(_T("%d"), coefficient);
		//MessageBox(0, strInfo, NULL);
		// 更改光标形状
		BeginWaitCursor();
		if (coefficient == 99.9) {
			int page = 1;
			if (lpSrcBitCount == 24) page = 3;
			if (lpSrcBitCount == 8) page = 1;
			int changing = constant;
			//std::cout << changing;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					for (int l = 0; l < page; l++) {
						lpSrcData = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * page + l;
						int temp = *lpSrcData + changing;
						if (temp < 0) {
							*lpSrcData = 0;
						}
						else if (temp > 255) {
							*lpSrcData = 255;
						}
						else {
							*lpSrcData = (unsigned char)(temp + 0.5);
						}
					}

				}
			}
			// 设置脏标记
			pDoc->SetModifiedFlag(TRUE);
			// 更新视图
			pDoc->UpdateAllViews(NULL);
		}
		else {
			//AfxMessageBox(L"!");
			if (Template24(lpSrcStartBits, lSrcWidth, lSrcHeight,
				iTempH, iTempW, iTempMX, iTempMY, aValue, coefficient, constant))
			{
				// 设置脏标记
				pDoc->SetModifiedFlag(TRUE);
				// 更新视图
				pDoc->UpdateAllViews(NULL);
			}
			else
			{
				// 提示用户
				//MessageBox("分配内存失败！", "系统提示" , MB_ICONINFORMATION | MB_OK);
				AfxMessageBox(L"分配内存失败！系统提示");// 警告
			}
		}
			

		

		// 恢复光标
		EndWaitCursor();
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	}
}

//素描化
void CMFCTemplateView::Onsumiao()
{
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	//pDoc->OnOpenDocument(pDoc->GetPathName());
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	// TODO: 在此添加命令处理程序代码
	Mat gray, gray_inverse, dst;

	Mat src = imread(cvStr);

	if (!src.data) {
		AfxMessageBox(L"读取图像失败");
	}

	//1.转为灰度图
	cvtColor(src, gray, COLOR_BGRA2GRAY);

	//图像取反,三种取反的方法
	gray_inverse = ~gray;
	//imshow("gray_inverse", gray_inverse);

	//3 高斯模糊
	GaussianBlur(gray_inverse, gray_inverse, Size(15, 15), 50, 50);
	//imshow("GaussianBlur", gray_inverse);

	//4 颜色减淡混合
	divide(gray, 255 - gray_inverse, dst, 255);
	
	cv::String aftername = "素描化" + cvStr;
	cv::imwrite(aftername, dst);

	std::string c = aftername;
	CString a = A2W(c.c_str());

	CString strInfo;
	strInfo.Format(_T("图片已保存到%s"), a);
	AfxMessageBox(strInfo);
	imshow("素描化风格", dst);
	waitKey(0);
}

//卡通化
void CMFCTemplateView::Oncartoon()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	//pDoc->OnOpenDocument(pDoc->GetPathName());
	USES_CONVERSION;  
	cv::String cvStr = W2A(pDoc->GetPathName());

	Mat src = imread(cvStr, IMREAD_COLOR);
	Mat result;
	stylization(src, result, 5, 0.6);

	cv::String aftername = "卡通化" + cvStr;
	cv::imwrite(aftername, result);

	std::string c = aftername;
	CString a = A2W(c.c_str());

	CString strInfo;
	strInfo.Format(_T("图片已保存到%s"), a);
	AfxMessageBox(strInfo);

	imshow("Stylization", result);
}




void CMFCTemplateView::Onyouhua()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());//获取路径
	Mat src = imread(cvStr, IMREAD_COLOR);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	//中值滤波降噪
	medianBlur(gray, gray, 5);

	//Laplacian边缘提取
	Laplacian(gray, gray, CV_8U, 3);


	//二值化边缘图像
	Mat mask(src.size(), CV_8U);
	threshold(gray, mask, 120, 255, THRESH_BINARY_INV);

	//对原始图像双边滤波
	//缩小原始图像
	Size tmpdst(src.cols / 2, src.rows / 2);
	Mat srctmp = Mat(tmpdst, src.type());
	resize(src, srctmp, tmpdst, 0, 0, INTER_LINEAR);
	Mat tmp = Mat(tmpdst, CV_8UC3);

	//双边滤波处理图像
	//像素邻域的直径范围
	int dsize = 5;
	double sColor = 30;
	double sSpace = 10;
	//迭代次数
	int iterator = 5;
	for (int i = 0; i < iterator; i++) {
		bilateralFilter(srctmp, tmp, dsize, sColor, sSpace);
		bilateralFilter(tmp, srctmp, dsize, sColor, sSpace);
	}

	//将处理完的图像缩放至原图大小再进行掩膜叠加
	Mat srcbak;
	resize(srctmp, srcbak, src.size(), 0, 0, INTER_LINEAR);
	//掩膜叠加
	Mat dst = Mat(src.size(), src.type(), Scalar::all(0)); //初始化
	srcbak.copyTo(dst, mask);


	cv::String aftername = "油画风" + cvStr;
	cv::imwrite(aftername, dst);

	std::string c = aftername;
	CString a = A2W(c.c_str());

	CString strInfo;
	strInfo.Format(_T("图片已保存到%s"), a);
	AfxMessageBox(strInfo);

	//显示图像
	imshow("油画风", dst);

	//pDoc->GetPathName() = strInfo;


}
#include <vector>
#include <bitset>

/*
	为图片添加数字水印。
	思想：把数字串转为二进制字符串（n位），再插入到原图的前n位。
	为了便于解码，先把图片所有像素转为偶数。
	设待插入二进制字符串a[n]，若a[n]==1，则像素值不变，若a[m]==0,则像素值减一。
	解码时通过奇偶性复原字符串。
*/
//输入框头文件 用于输入
#include "yinxie.h"
void CMFCTemplateView::Onshuiyin()
{
	CString strInfo;//debug用
	
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	unsigned char* lpSrcData = 0;
	long  lSrcLineBytes;		//图象每行的字节数
	long	  lSrcWidth;      //图象的宽度和高度
	long	  lSrcHeight;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图
	begin:
	yinxie dlgPara;//创建对话框
	if (dlgPara.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	
	int me =dlgPara.num;	//获取字符串
	if (me <= 0 || me>1000) {
		//鲁棒检查
		AfxMessageBox(L"密文不符合条件，请重新输入。");
		goto begin;
	}
	int j = 0;	//二进制字符串位数
	int a[14]={0};//二进制字符串
	//将密文转为二进制序列
	int a1 = 0,b1 = 0;
	for (; me > 0; me /= 2) {
		a[a1++] = me % 2;
	}
	//对数组倒序
	int nm[14] = { 0 };
	int i1, j1;
	for (i1 = 0, j1 = 13; i1 < 14, j1 >= 0; ++i1, --j1)
	{
		nm[i1] = a[j1];
	}

	int i;
	
	//先将需要的像素全部变成偶数
	int mr = 0; int yu = 0;
	for (int h = 0; h < lSrcHeight; h++) {
		for (int w = 0; w < lSrcWidth; w++) {
			lpSrcData = (unsigned char*)lpSrcDib + lSrcLineBytes * (lSrcHeight - 1 - h) + w;
			//避免255向前越界
			if (*lpSrcData == 255) {
				*lpSrcData = 254;
			}

			if (*lpSrcData % 2 != 0) {
				*lpSrcData = *lpSrcData+ 1;
			}
			mr++;
			if (mr == 14) {
				//只将需要用到的区段偶数化
				yu = 0;
				break;
			}
		}
		if (yu == 0) {
			break;
		}
	}
	int flag = 0;//判断已经嵌入了几位
	int nu = 0; int bj = 0;
	
	for (int h = 0; h < lSrcHeight; h++) {
		for (int w = 0; w < lSrcWidth; w++) {
			//AfxMessageBox(L"C");
			lpSrcData = (unsigned char*)lpSrcDib + lSrcLineBytes * (lSrcHeight - 1 - h) + w;
			CString strInfo;
			strInfo.Format(_T("像素值=%d"), *lpSrcData);
			//AfxMessageBox(strInfo);
			if (nm[nu] == 0&& bj == 0) {
				//如果二进制字符串该位为0，则不做改变。
				flag++;
			}
			else if (nm[nu] == 1 && bj == 0) {
				//如果二进制字符串该位为0，则-1，变成奇数。
				if (*lpSrcData == 0) {
					*lpSrcData += 1;
				}
				else {
					*lpSrcData -= 1;
				}
				flag++;
			}
			if (flag == 14) {
				//全部嵌入完成
				bj = 1;	
				break;
			}
			nu++;
		}
		if (bj==1) {
			//全部嵌入完成，跳出
			AfxMessageBox(L"嵌入成功！");
			break;
		}
	}
	
	// 设置脏标记
	pDoc->SetModifiedFlag(TRUE);
	// 更新视图
	pDoc->UpdateAllViews(NULL);
	//::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}



//二进制转十进制
int conversion(int binaryNumber)
{
	int decimalNumber = 0, i = 0, n;
	while (binaryNumber != 0)
	{
		n = binaryNumber % 10;
		binaryNumber /= 10;
		decimalNumber += n * pow(2, i);
		++i;
	}
	return decimalNumber;
}
//水印解码
void CMFCTemplateView::Onjiema()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	unsigned char* lpSrcData = 0;
	long  lSrcLineBytes;		//图象每行的字节数
	long	  lSrcWidth;      //图象的宽度和高度
	long	  lSrcHeight;
	int    lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图
	CString strInfo;
	//解码
	int len = 5;
	int b[20] = { 0 };
	int s = 0; int flag = 1;
	for (int h = 0; h < lSrcHeight ; h++) {
		for (int w = 0; w < lSrcWidth ; w++) {
			lpSrcData = (unsigned char*)lpSrcDib + lSrcLineBytes * (lSrcHeight - 1 - h) + w;
			
			if (*lpSrcData % 2 == 0) {
				b[s] = 0;
			}
			else {
				b[s] = 1;
			}
			
			//解码完成
			if (s == 14) {
				flag = 0;
				break;
			}
			s++;
		}
		if (flag == 0) {
			break;
		}
	}
	
	int i = 0;
	int n = 0;
	//计算左对齐的无效0有多少个
	while (b[i] == 0) {
		n++;//无效0个数
		i++;
	}
	int c[20] = { 0 };
	int k = 0;
	for (int u =n; u < 14; u++) {
		c[k] = b[u];//剔除无效0后的二进制
		k++;
	}
	strInfo.Format(_T("k= %d"),k);
	int sum = 0;
	k++;
	//将二进制数组转为单个数
	for (int l = 0; l < k-1; l++) {
		sum = sum * 10 + c[l];
	}
	sum = conversion(sum);//转为十进制
	//显示解码结果
	strInfo.Format(_T("解码结果：%d"), sum);
	AfxMessageBox(strInfo);
}


#include "Coursedesign.h"
#include "use.h"
#include "useres.h"
RNG g_rng(12345);

void CMFCTemplateView::Onuse()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;								//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
																	/////////////////////////////////////////////////////////////////////////////////////////////////	
	use  dlg;// 创建对话框

	int my_choice;
	int my_link;

	int my_number = 0;
	double my_area = 0;
	double my_meter;
	double my_circle;
	double my_square;
	if (dlg.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}
	
	my_choice = dlg.m_foreground;
	my_link = dlg.m_link;
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	Mat src_image = imread(cvStr);
	//出错判断
	if (!src_image.data)
	{
		AfxMessageBox(L"src image load failed!");
	}
	//显示原图
	//namedWindow("原图", WINDOW_NORMAL);
	//imshow("原图", src_image);

	//高斯滤波去噪声（没用）
	Mat blur_image;
	GaussianBlur(src_image, blur_image, Size(3, 3), 0, 0);
	//imshow("GaussianBlur", blur_image);

	//灰度变换与二值化（没用）
	Mat gray_image, binary_image;
	cvtColor(blur_image, gray_image, COLOR_BGR2GRAY);
	int num_labels;
	if (my_link == 0)//4联通
	{
		if (dlg.m_foreground == 0)//黑
		{
			threshold(gray_image, binary_image, 100, 255, THRESH_BINARY_INV);
			//计算连通域
			Mat labels = Mat::zeros(gray_image.size(), CV_32S);
			num_labels = connectedComponents(binary_image, labels, 4, CV_32S);


			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
		}
		if (dlg.m_foreground == 1)//白
		{
			threshold(gray_image, binary_image, 100, 255, THRESH_BINARY);
			Mat labels = Mat::zeros(gray_image.size(), CV_32S);
			num_labels = connectedComponents(binary_image, labels, 4, CV_32S);

			my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
		}
		if (dlg.m_foreground == 2)//自动
		{
			unsigned char* img;
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;//i行j列
					if (*img == 0)
						black++;
					else
						white++;
				}
			}
			if (black >= white)//白
			{
				threshold(gray_image, binary_image, 100, 255, THRESH_BINARY);
				Mat labels = Mat::zeros(gray_image.size(), CV_32S);
				num_labels = connectedComponents(binary_image, labels, 4, CV_32S);

				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			}
			else//黑
			{
				threshold(gray_image, binary_image, 100, 255, THRESH_BINARY_INV);
				Mat labels = Mat::zeros(gray_image.size(), CV_32S);
				num_labels = connectedComponents(binary_image, labels, 4, CV_32S);

				my_number = dealer_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_area = getArea_four(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			}
		}

	}

	if (my_link == 1)//8联通
	{
		if (dlg.m_foreground == 0)//黑
		{
			threshold(gray_image, binary_image, 100, 255, THRESH_BINARY_INV);
			Mat labels = Mat::zeros(gray_image.size(), CV_32S);
			num_labels = connectedComponents(binary_image, labels, 8, CV_32S);

			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			//my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
		}
		if (dlg.m_foreground == 1)//白
		{
			threshold(gray_image, binary_image, 100, 255, THRESH_BINARY);
			Mat labels = Mat::zeros(gray_image.size(), CV_32S);
			num_labels = connectedComponents(binary_image, labels, 8, CV_32S);

			my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
			my_meter = sqrt(my_area / 3.14) * 2 * 3.14;
		}
		if (dlg.m_foreground == 2)//自动
		{
			unsigned char* img;
			int black = 0, white = 0;
			for (int i = 0; i < lSrcHeight; i++) {
				for (int j = 0; j < lSrcWidth; j++) {
					img = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;//i行j列
					if (*img == 0)
						black++;
					else
						white++;
				}
			}
			if (black >= white)//白
			{
				threshold(gray_image, binary_image, 100, 255, THRESH_BINARY);
				Mat labels = Mat::zeros(gray_image.size(), CV_32S);
				num_labels = connectedComponents(binary_image, labels,8, CV_32S);
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 255);
				
			}
			else//黑
			{
				threshold(gray_image, binary_image, 100, 255, THRESH_BINARY_INV);
				Mat labels = Mat::zeros(gray_image.size(), CV_32S);
				num_labels = connectedComponents(binary_image, labels, 8, CV_32S);
				my_number = dealer_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
				my_area = getArea_eight(lpSrcStartBits, lSrcWidth, lSrcHeight, 0);
			}
		}

	}
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	
	//imshow("binary", binary_image);

	//形态学闭操作(粘合断开的区域)（没用）
	Mat morph_image;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary_image, morph_image, MORPH_CLOSE, kernel, Point(-1, -1), 1);
	//imshow("morphology", morph_image);

	//查找所有外轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	findContours(binary_image, contours, hireachy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	//定义结果图
	Mat result_image = Mat::zeros(src_image.size(), CV_8UC3);

	//初始化周长、面积、圆形度、周径比
	double len = 0, area = 0, roundness = 0;
	float squareness=0;

	//循环找出所有符合条件的轮廓
	long max = 0;
	int cX = 0;
	int cY = 0;
	int num = 0;
	for (size_t t = 0; t < contours.size(); t++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255),
		g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		//条件：过滤掉小的干扰轮廓
		Rect rect = boundingRect(contours[t]);		//垂直边界最小矩形
		if (rect.width < 10)
			continue;
		//画出找到的轮廓
		drawContours(result_image, contours, t, color, 1, 8, hireachy);
	
		//绘制轮廓的最小外接矩形
		RotatedRect minrect = minAreaRect(contours[t]);	//最小外接矩形
		int minrectmianji = minrect.size.height * minrect.size.width;
		Point2f P[4];			//四个顶点坐标
		minrect.points(P);
		for (int j = 0; j <= 3; j++)
		{
			line(result_image, P[j], P[(j + 1) % 4], color, 1);
		}

		//绘制轮廓的最小外结圆
		Point2f center;
		float radius;
		minEnclosingCircle(contours[t], center, radius);		//最小外接圆
		circle(result_image, center, radius, color, 1);

		
		if (minrectmianji > max) {
			//计算面积、周长、圆形度、周径比
			area = contourArea(contours[t]);//计算轮廓面积
			len = arcLength(contours[t], true);//计算轮廓周长

			roundness = (4 * CV_PI * area) / (len * len);//圆形度
			max = minrectmianji;
			squareness = area / max;
			//计算最大轮廓的中心
			cX = int(moments(contours[t]).m10 / moments(contours[t]).m00);
			cY = int(moments(contours[t]).m01 / moments(contours[t]).m00);
		}
		num = t;
	}
	
	useres  Dlg;// 创建对话框

	Dlg.m_Num = num_labels -1;
	Dlg.m_mSquare = area;
	Dlg.m_mCmeter = len;
	Dlg.m_circle = roundness;
	Dlg.m_square = squareness;
	Dlg.m_x = cX;
	Dlg.m_y = cY;
	if (Dlg.DoModal() != IDOK)// 显示对话框，设定平移量
	{
		return;
	}

	//显示结果
	namedWindow("轮廓图", WINDOW_NORMAL);
	imshow("轮廓图", result_image);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}

#include "canny.h"
void CMFCTemplateView::OnCanny()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();
	long lSrcLineBytes;		//图象每行的字节数
	long lSrcWidth;      //图象的宽度和高度
	long lSrcHeight;
	int lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	// 更改光标形状
	BeginWaitCursor();

	// 循环控制变量
	int y;
	int x;

	// 开辟内存，存储图像数据
	unsigned char* pUnchImage = new unsigned char[lSrcWidth * lSrcHeight];

	for (y = 0; y < lSrcHeight; y++)
	{
		for (x = 0; x < lSrcWidth; x++)
		{
			pUnchImage[y * lSrcWidth + x] = lpSrcStartBits[y * lSrcLineBytes + x];
		}
	}

	// canny 算子计算后的结果
	unsigned char* pUnchEdge = new unsigned char[lSrcWidth * lSrcHeight];

	// 调用 canny 函数进行边界提取
	Canny(pUnchImage, lSrcWidth, lSrcHeight, 0.4, 0.4, 0.79, pUnchEdge);

	for (y = 0; y < lSrcHeight; y++)
	{
		for (x = 0; x < lSrcWidth; x++)
		{
			lpSrcStartBits[y * lSrcWidth + x] = (unsigned char)(255 - pUnchEdge[y * lSrcWidth + x]);
		}
	}

	// 释放内存
	delete[]pUnchImage;
	pUnchImage = NULL;
	delete[]pUnchEdge;
	pUnchEdge = NULL;
	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标形状
	EndWaitCursor();

	// 刷新屏幕
	Invalidate();
}

/*
void CMFCTemplateView::Ontst()
{
	// TODO: 在此添加命令处理程序代码
	//载入原图 
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long    lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;								//判断是否是8-bpp位图,不是则返回	
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);		// 计算图象每行的字节数
	USES_CONVERSION;
	cv::String cvStr = W2A(pDoc->GetPathName());
	Mat image = imread(cvStr);

	//创建窗口 
	namedWindow("【原图】腐蚀操作");
	namedWindow("【效果图】腐蚀操作");

	//显示原图
	imshow("【原图】腐蚀操作", image);


	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;

	//进行腐蚀操作
	erode(image, out, element);

	//显示效果图
	imshow("【效果图】腐蚀操作", out);

	waitKey(0);

}
*/

void CMFCTemplateView::Onimgzaoshengjy()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针，指向信息头
	LPSTR	lpSrcStartBits;	//指向源像素的指针，指向位图数据
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//循环变量
	long i;
	long j;
	//生成伪随机种子
	srand((unsigned)time(NULL));

	//在图像中加噪
	for (j = 0; j < lSrcHeight; j++)
	{
		for (i = 0; i < lSrcLineBytes; i++)
		{
			if (rand() > 28000)
			{
				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrcDib = (char*)lpSrcStartBits + lSrcLineBytes * j + i;

				//图像中当前点置为黑
				*lpSrcDib = 0;
			}
		}
	}
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//Invalidate();  //OK
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCTemplateView::Onimgzaoshengsj()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针，指向信息头
	LPSTR	lpSrcStartBits;	//指向源像素的指针，指向位图数据
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	//循环变量
	long i;
	long j;
	//像素值
	unsigned char pixel;

	//噪声
	BYTE NoisePoint;

	//生成伪随机种子
	srand((unsigned)time(NULL));

	//在图像中加噪
	for (j = 0; j < lSrcHeight; j++)
	{
		for (i = 0; i < lSrcLineBytes; i++)
		{
			NoisePoint = rand() / 1024;

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrcDib = (char*)lpSrcStartBits + lSrcLineBytes * j + i;

			//取得像素值
			pixel = (unsigned char)*lpSrcDib;

			*lpSrcDib = (unsigned char)(pixel * 224 / 256 + NoisePoint);
		}
	}
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//Invalidate();  //OK
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
}


void CMFCTemplateView::OnMinlb()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针，指向信息头
	LPSTR	lpSrcStartBits;	//指向源像素的指针，指向位图数据
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 指向源图像的指针
	unsigned char* lpSrc;
	// 指向要复制区域的指针
	unsigned char* lpDst;
	// 指向复制图像的指针
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;
	// 指向滤波器数组的指针
	unsigned char* aValue;
	HLOCAL			hArray;
	int iFilterH = 3;
	int iFilterW = 3;
	int iFilterMX = 1;//模板中心元素X坐标
	int iFilterMY = 1;//模板中心元素Y坐标
	// 循环变量
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lSrcLineBytes * lSrcHeight);

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpSrcStartBits, lSrcLineBytes * lSrcHeight);
	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	// 锁定内存
	aValue = (unsigned char*)LocalLock(hArray);

	// 行(除去边缘几行)
	for (i = iFilterMY; i < lSrcHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iFilterMX; j < lSrcWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			//lpDst = (unsigned char*)lpNewDIBBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;
					//最大 lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;
					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			unsigned char* bArray = aValue;
			int iFilterLen = iFilterH * iFilterW;
			// 循环变量
			int		i;
			int		j;
			// 中间变量
			unsigned char bTemp;
			// 用冒泡法对数组进行排序
			for (j = 0; j < iFilterLen - 1; j++)
			{
				for (i = 0; i < iFilterLen - j - 1; i++)
				{
					if (bArray[i] > bArray[i + 1])
					{
						// 互换
						bTemp = bArray[i];
						bArray[i] = bArray[i + 1];
						bArray[i + 1] = bTemp;
					}
				}
			}
			/*
			for (j = 0; j < iFilterLen - 1; j++)
			{
				for (i = 0; i < iFilterLen - j - 1; i++)
				{
					if (bArray[i] > bArray[i + 1])
					{
						// 互换
						bTemp = bArray[i];
						bArray[i] = bArray[i + 1];
						bArray[i + 1] = bTemp;
					}
				}
			}
			*/
			bTemp = bArray[0];
			*lpDst = bTemp;
		}
	}
	// 复制变换后的图像
	memcpy(lpSrcStartBits, lpNewDIBBits, lSrcLineBytes * lSrcHeight);
	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}


void CMFCTemplateView::OnMaxlb()
{
	// TODO: 在此添加命令处理程序代码
	CMFCTemplateDoc* pDoc = GetDocument();// 获取文档		
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针，指向信息头
	LPSTR	lpSrcStartBits;	//指向源像素的指针，指向位图数据
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);			// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);					// 获取图象的宽度		
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);					// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	// 指向源图像的指针
	unsigned char* lpSrc;
	// 指向要复制区域的指针
	unsigned char* lpDst;
	// 指向复制图像的指针
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;
	// 指向滤波器数组的指针
	unsigned char* aValue;
	HLOCAL	hArray;
	int iFilterH = 3;
	int iFilterW = 3;
	int iFilterMX = 1;//模板中心元素X坐标
	int iFilterMY = 1;//模板中心元素Y坐标
	// 循环变量
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lSrcLineBytes * lSrcHeight);

	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpSrcStartBits, lSrcLineBytes * lSrcHeight);
	// 暂时分配内存，以保存滤波器数组
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	// 锁定内存
	aValue = (unsigned char*)LocalLock(hArray);

	// 行(除去边缘几行)
	for (i = iFilterMY; i < lSrcHeight - iFilterH + iFilterMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iFilterMX; j < lSrcWidth - iFilterW + iFilterMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;
			// 读取滤波器数组
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// 指向DIB第i - iFilterMY + k行，第j - iFilterMX + l个象素的指针
					lpSrc = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;

					// 保存象素值
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			unsigned char* bArray = aValue;
			int iFilterLen = iFilterH * iFilterW;
			// 循环变量
			int		i;
			int		j;
			// 中间变量
			unsigned char bTemp;
			// 用冒泡法对数组进行排序
			for (j = 0; j < iFilterLen - 1; j++)
			{
				for (i = 0; i < iFilterLen - j - 1; i++)
				{
					if (bArray[i] > bArray[i + 1])
					{
						// 互换
						bTemp = bArray[i];
						bArray[i] = bArray[i + 1];
						bArray[i + 1] = bTemp;
					}
				}
			}
			bTemp = bArray[iFilterLen - 1];
			*lpDst = bTemp;
		}
	}
	// 复制变换后的图像
	memcpy(lpSrcStartBits, lpNewDIBBits, lSrcLineBytes * lSrcHeight);
	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	pDoc->SetModifiedFlag(true);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
	EndWaitCursor();
}
