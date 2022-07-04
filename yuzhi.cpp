// Yuzhifenge.cpp: 实现文件
//
#include "stdafx.h"
//#include "pch.h"
#include "MFCTemplate.h"
#include "Yuzhi.h"
#include "afxdialogex.h"


// Yuzhifenge 对话框

IMPLEMENT_DYNAMIC(Yuzhifenge, CDialogEx)

Yuzhifenge::Yuzhifenge(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Yuzhi, pParent)
	, m_threshold(0)
{

}

Yuzhifenge::~Yuzhifenge()
{
}

void Yuzhifenge::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	if (m_threshold == 256) {
		int k=0;
		DDX_Text(pDX, IDC_EDIT1, k);
	}
	else {
		
		DDX_Text(pDX, IDC_EDIT1, m_threshold);
	}
	OnPaint();
}


BEGIN_MESSAGE_MAP(Yuzhifenge, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &Yuzhifenge::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Yuzhifenge::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Yuzhifenge::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &Yuzhifenge::OnBnClickedRadio4)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Yuzhifenge::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &Yuzhifenge::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_BN_CLICKED(IDC_BUTTONYULAN, &Yuzhifenge::OnBnClickedButtonyulan)
ON_BN_CLICKED(IDC_Byl, &Yuzhifenge::OnBnClickedByl)
ON_BN_CLICKED(IDC_BUTTONhuifu, &Yuzhifenge::OnBnClickedButtonhuifu)
//ON_BN_CLICKED(IDC_RADIO4, &Yuzhifenge::OnBnClickedRadio4)
END_MESSAGE_MAP()


// Yuzhifenge 消息处理程序


void Yuzhifenge::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GroupSelect = 0;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(false);
}


void Yuzhifenge::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GroupSelect = 1;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(false);
}


void Yuzhifenge::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GroupSelect = 2;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(false);
}
void Yuzhifenge::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GroupSelect = 3;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(true);
}


BOOL Yuzhifenge::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//获取绘制图形的标签
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	//计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);
	
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	//设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	//初始化拖动状态
	m_bIsDrawing = FALSE;
	ifyulan = 0;//是否预览

	return true;
}


void Yuzhifenge::OnEnKillfocusEdit1()
{

	// TODO: 在此添加控件通知处理程序代码
	//保存用户设置
	UpdateData(TRUE);
	//重绘
	InvalidateRect(m_MouseRect, TRUE);
}


void Yuzhifenge::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	//printf("%d", m_GroupSelect);
	UpdateData(true);
	int t = m_GroupSelect;
	if (t == 0)
	{
		UpdateData(true);
		m_threshold = temp1;
		OnPaint();
		UpdateData(FALSE);
	}
	if (t == 1)
	{
		UpdateData(true);
		m_threshold = temp2;
		OnPaint();
		UpdateData(FALSE);
	}
	if (t == 2)
	{
		UpdateData(true);
		m_threshold = temp3;

		OnPaint();
		UpdateData(FALSE);
	}
	if (t == 3)
	{
		UpdateData(true);
		m_threshold = temp4;

		OnPaint();
		UpdateData(FALSE);
	}
}


void Yuzhifenge::OnPaint()
{
	CPaintDC dc(this); 
    //获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_STATIC);
	//字符串
	CString str;
	CPoint pLeft, pRight, pCenterTop, pCenterTop2, pCenterBottom;
	//指针
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	//创建画笔对象
	CPen* pPenRed = new CPen;
	//红色画笔，红绿蓝
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//创建画笔对象
	CPen* pPenBlue = new CPen;
	//蓝色画笔，红绿蓝
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//创建画笔对象
	CPen* pPenGreen = new CPen;
	//绿色画笔，红绿蓝
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	//绘制坐标轴
	pDC->MoveTo(10, 10);
	//垂直轴
	pDC->LineTo(10, 280);
	//水平轴
	pDC->LineTo(320, 280);
	//写坐标
	str.Format(_T("0"));
	pDC->TextOut(10, 281, str);
	str.Format(_T("255"));
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	//绘制X箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	//绘制Y箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);
	//更改成绿色画笔,画垂直线
	if (m_threshold == 256){
		pDC->SelectObject(pPenGreen);
			pCenterTop.x = 10 + 0;
			pCenterTop.y = 25;

			pCenterBottom.x = 10 + 0;
			pCenterBottom.y = 280;
			pDC->MoveTo(pCenterTop);
			pDC->LineTo(pCenterBottom);

			//更改成蓝色画笔
			pDC->SelectObject(pPenBlue);
		pLeft.x = 10;
		pLeft.y = 280;
		pDC->MoveTo(pLeft);
		pCenterTop2.x = 10 + 0;
		pCenterTop2.y = 280;
		pDC->LineTo(pCenterTop2);
		pCenterTop.x = 10 + 0;
		pCenterTop.y = 10;
		pDC->LineTo(pCenterTop);
		pRight.x = 265;
		pRight.y = 10;
		pDC->LineTo(pRight);
	}
	else {
		pDC->SelectObject(pPenGreen);
		pCenterTop.x = 10 + m_threshold;//128;
		pCenterTop.y = 25;

		pCenterBottom.x = 10 + m_threshold;//128;
		pCenterBottom.y = 280;
		pDC->MoveTo(pCenterTop);
		pDC->LineTo(pCenterBottom);

		//更改成蓝色画笔
		pDC->SelectObject(pPenBlue);
		pLeft.x = 10;
		pLeft.y = 280;
		pDC->MoveTo(pLeft);
		pCenterTop2.x = 10 + m_threshold;//128;
		pCenterTop2.y = 280;
		pDC->LineTo(pCenterTop2);
		pCenterTop.x = 10 + m_threshold;//128;
		pCenterTop.y = 10;
		pDC->LineTo(pCenterTop);
		pRight.x = 265;
		pRight.y = 10;
		pDC->LineTo(pRight);
	}
	
}


void Yuzhifenge::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  当用户单击鼠标左键开始拖动
		//判断是否在有效区域
	if (m_MouseRect.PtInRect(point))
	{
		if (m_MouseRect.left <= point.x <= (m_MouseRect.left + m_threshold))
		{
			//设置拖动状态
			m_bIsDrawing = TRUE;
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	//默认
	CDialogEx::OnLButtonDown(nFlags, point);
}


void Yuzhifenge::OnLButtonUp(UINT nFlags, CPoint point)
{
	//  当用户释放鼠标左键停止拖动
	if (m_bIsDrawing)
	{
		//重新设置拖动状态
		m_bIsDrawing = FALSE;
	}
	//默认
	CDialogEx::OnLButtonUp(nFlags, point);
}


void Yuzhifenge::OnMouseMove(UINT nFlags, CPoint point)
{
	//  判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		//判断是否在拖动
		if (m_bIsDrawing)
		{
			//更改阈值
			m_threshold = (BYTE)(point.x - m_MouseRect.left);
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			//更新
			UpdateData(FALSE);
			//重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_threshold))
		{
			//更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	//默认
	CDialogEx::OnMouseMove(nFlags, point);
}

int WINAPI ThresholdDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes)
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

			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;
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
		p1 = 0; p2 = 0; s1 = 0; s2 = 0;
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

int WINAPI OTSUDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes)
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
			lpSrc = (char*)lpDIBBits + lLineBytes * j + i;

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
		p1 = 0; p2 = 0; s1 = 0; s2 = 0;
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

void RegionSegAdaptive(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes) {

	int y, x;

	int nThd[2][2] = { 0 };
	int Location;
	//左上
	Location = 0;
	for (y = 0; y < lHeight / 2; y++)
		for (x = 0; x < lWidth / 2; x++) {
			Location += lpDIBBits[y * lLineBytes + x];
		}
	Location /= ((lHeight / 2) * (lWidth / 2));
	nThd[0][0] = Location;

	for (y = 0; y < lHeight / 2; y++)
		for (x = 0; x < lWidth / 2; x++) {
			if (lpDIBBits[y * lLineBytes + x] < nThd[0][0])
				lpDIBBits[y * lLineBytes + x] = 255;
			else
				lpDIBBits[y * lLineBytes + x] = 0;
		}
	//左下
	Location = 0;
	for (y = lHeight / 2; y < lHeight; y++)
		for (x = 0; x < lWidth / 2; x++) {
			Location += lpDIBBits[y * lLineBytes + x];
		}
	Location /= ((lHeight - lHeight / 2) * (lWidth / 2));
	nThd[1][0] = Location;

	for (y = lHeight / 2; y < lHeight; y++)
		for (x = 0; x < lWidth / 2; x++) {
			if (lpDIBBits[y * lLineBytes + x] < nThd[1][0])
				lpDIBBits[y * lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y * lLineBytes + x] = (unsigned char)0;
		}
	//右上
	Location = 0;
	for (y = 0; y < lHeight / 2; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			Location += lpDIBBits[y * lLineBytes + x];
		}
	Location /= ((lHeight / 2) * (lWidth - lWidth / 2));
	nThd[0][1] = Location;

	for (y = 0; y < lHeight / 2; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			if (lpDIBBits[y * lLineBytes + x] < nThd[0][1])
				lpDIBBits[y * lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y * lLineBytes + x] = (unsigned char)0;
		}
	//右下
	Location = 0;
	for (y = lHeight / 2; y < lHeight; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			Location += lpDIBBits[y * lLineBytes + x];
		}
	Location /= ((lHeight - lHeight / 2) * (lWidth - lWidth / 2));
	nThd[1][1] = Location;

	for (y = lHeight / 2; y < lHeight; y++)
		for (x = lWidth / 2; x < lWidth; x++) {
			if (lpDIBBits[y * lLineBytes + x] < nThd[1][1])
				lpDIBBits[y * lLineBytes + x] = (unsigned char)255;
			else
				lpDIBBits[y * lLineBytes + x] = (unsigned char)0;
		}
	for (y = 0; y < lHeight; y++)
		for (x = 0; x < lWidth; x++) {
			lpDIBBits[y * lLineBytes + x] = 255 - lpDIBBits[y * lLineBytes + x];
		}
}

//双峰法,要求图像的直方图是双峰的
int WINAPI DF(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int bitcount) {
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
//预览按钮，在预览按钮中执行一遍
void Yuzhifenge::OnBnClickedByl()
{	
	ifyulan = 1;
	//AfxMessageBox(L"Cll");
	for (int i = 0; i < lSrcHeight; i++) {
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrcStartBits[i * lSrcWidth + j] = StartBits[i * lSrcWidth + j];
		}
	}
	//if (!lpSrcDib) return;
	//lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);
	//lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);// 获取图象的高度		
	//lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);
	//lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图象每行的字节数
	//lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);//图像像素
	//lLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);
	int i, j;
	
	temp1 = ThresholdDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, lLineBytes);
	temp2 = OTSUDIB(lpSrcStartBits, lSrcWidth, lSrcHeight, lLineBytes);
	temp3 = m_threshold;
	temp4= DF(lpSrcStartBits, lSrcWidth, lSrcHeight, lpSrcBitCount);

	int threshold = m_threshold;
	if (m_GroupSelect != 2)
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
	else if (m_GroupSelect == 2)
	{
		//AfxMessageBox(L"!");
		//dlgPara1.m_threshold = temp3;
		RegionSegAdaptive(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes);
	}

	pDoc->SetModifiedFlag(false);
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);
}


void Yuzhifenge::OnBnClickedButtonhuifu()
{
	ifyulan = 0;//是否预览
	// 恢复图片,将原图片数据拷贝给现在的图片
	for (int i = 0; i < lSrcHeight ; i++) {
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrcStartBits[i * lSrcWidth + j] = StartBits[i * lSrcWidth + j];
		}
	}
		

	// 设置脏标记
	pDoc->SetModifiedFlag(false);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);
}



