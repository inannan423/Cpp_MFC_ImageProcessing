// Lashen.cpp: 实现文件
//
#include "stdafx.h"
//#include "pch.h"
#include "MFCTemplate.h"
#include "iostream"
#include "Lashen.h"
#include "afxdialogex.h"
#include "MFCTemplateView.h"
#include <opencv2/opencv.hpp>
//std::vector<cv::Mat> planes;
//cv::Mat complexImage;
// Lashen 对话框

IMPLEMENT_DYNAMIC(Lashen, CDialogEx)

Lashen::Lashen(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Lashen, pParent)
	, m_1x(0)
	, m_1y(0)
	, m_2x(0)
	, m_2y(0)
{

}

Lashen::~Lashen()
{
}

void Lashen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_1x);
	DDX_Text(pDX, IDC_EDIT2, m_1y);
	DDV_MinMaxByte(pDX, m_1y, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, m_2x);
	DDV_MinMaxByte(pDX, m_2x, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, m_2y);
	DDV_MinMaxByte(pDX, m_2y, 0, 255);
}


BEGIN_MESSAGE_MAP(Lashen, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Lashen::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &Lashen::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &Lashen::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &Lashen::OnEnKillfocusEdit4)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &Lashen::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Lashen::OnBnClickedButton2)
END_MESSAGE_MAP()


// Lashen 消息处理程序


BOOL Lashen::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_STATIC);

	// 计算接受鼠标事件的有效区域

	pWnd->GetClientRect(m_MouseRect);

	pWnd->ClientToScreen(&m_MouseRect);



	CRect rect;

	GetClientRect(rect);

	ClientToScreen(&rect);



	m_MouseRect.top -= rect.top;

	m_MouseRect.left -= rect.left;



	// 设置接受鼠标事件的有效区域

	m_MouseRect.top += 25;

	m_MouseRect.left += 10;

	m_MouseRect.bottom = m_MouseRect.top + 255;

	m_MouseRect.right = m_MouseRect.left + 256;



	// 初始化拖动状态

	m_iIsDraging = 0;
	return TRUE;  // return TRUE unless you set the focus to a control

}


void Lashen::OnOK()
{

	if (m_1x > m_2x)
	{

		BYTE bTemp = m_1x;
		m_1x = m_2x;
		m_2x = bTemp;
		bTemp = m_1y;
		m_1y = m_2y;
		m_2y = bTemp;
		UpdateData(FALSE);

	}
	CDialog::OnOK();

}


void Lashen::OnEnKillfocusEdit1()
{
	// 更新
	UpdateData(TRUE);
	// 判断是否下限超过上限

	if (m_1x > m_2x)

	{

		// 互换

		BYTE bTemp = m_1x;
		m_1x = m_2x;
		m_2x = bTemp;
		bTemp = m_1y;
		m_1y = m_2y;
		m_2y = bTemp;
		UpdateData(FALSE);

	}
	InvalidateRect(m_MouseRect, TRUE);

}


void Lashen::OnEnKillfocusEdit2()
{
	UpdateData(TRUE);
	if (m_1x > m_2x)
	{
		BYTE bTemp = m_1x;
		m_1x = m_2x;
		m_2x = bTemp;
		bTemp = m_1y;
		m_1y = m_2y;
		m_2y = bTemp;
		UpdateData(FALSE);

	}
	InvalidateRect(m_MouseRect, TRUE);

}


void Lashen::OnEnKillfocusEdit3()
{
	UpdateData(TRUE);
	InvalidateRect(m_MouseRect, TRUE);
}


void Lashen::OnEnKillfocusEdit4()
{
	UpdateData(TRUE);

	InvalidateRect(m_MouseRect, TRUE);
}


void Lashen::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 当用户释放鼠标左键停止拖动

	if (m_iIsDraging != 0)
	{
		// 重置拖动状态
		m_iIsDraging = 0;
	}
	// 默认释放鼠标左键处理事件
	CDialog::OnLButtonUp(nFlags, point);
}


void Lashen::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 当用户单击鼠标左键开始拖动
	if (m_MouseRect.PtInRect(point))
	{
		CRect	rectTemp;
		// 计算点1临近区域
		rectTemp.left = m_MouseRect.left + m_1x - 2;
		rectTemp.right = m_MouseRect.left + m_1x + 2;
		rectTemp.top = 255 + m_MouseRect.top - m_1y - 2;
		rectTemp.bottom = 255 + m_MouseRect.top - m_1y + 2;

		// 判断用户是不是想拖动点1
		if (rectTemp.PtInRect(point))
		{
			// 设置拖动状态1，拖动点1
			m_iIsDraging = 1;
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		}
		else
		{
			// 计算点2临近区域
			rectTemp.left = m_MouseRect.left + m_2x - 2;
			rectTemp.right = m_MouseRect.left + m_2x + 2;
			rectTemp.top = 255 + m_MouseRect.top - m_2y - 2;
			rectTemp.bottom = 255 + m_MouseRect.top - m_2y + 2;

			// 判断用户是不是想拖动点2
			if (rectTemp.PtInRect(point))
			{
				// 设置拖动状态为2，拖动点2
				m_iIsDraging = 2;
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}
	// 默认单击鼠标左键处理事件
	CDialog::OnLButtonDown(nFlags, point);
}


void Lashen::OnMouseMove(UINT nFlags, CPoint point)
{
	// 判断当前光标是否在绘制区域
	if (m_MouseRect.PtInRect(point))
	{
		// 判断是否正在拖动
		if (m_iIsDraging != 0)
		{
			// 判断正在拖动点1还是点2
			if (m_iIsDraging == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_2x)
				{
					// 更改下限
					m_1x = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_1x = m_2x - 1;
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_2x - 1;
				}
				// 更改Y坐标
				m_1y = (BYTE)(255 + m_MouseRect.top - point.y);
			}
			else
			{
				// 正在拖动点2
				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_1x)
				{
					// 更改下限
					m_2x = (BYTE)(point.x - m_MouseRect.left);
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_2x = m_1x + 1;
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_1x + 1;
				}
				// 更改Y坐标
				m_2y = (BYTE)(255 + m_MouseRect.top - point.y);
			}
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			// 更新

			UpdateData(FALSE);
			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			CRect	rectTemp1;
			CRect	rectTemp2;

			// 计算点1临近区域
			rectTemp1.left = m_MouseRect.left + m_1x - 2;
			rectTemp1.right = m_MouseRect.left + m_1x + 2;
			rectTemp1.top = 255 + m_MouseRect.top - m_1y - 2;
			rectTemp1.bottom = 255 + m_MouseRect.top - m_1y + 2;

			// 计算点2临近区域
			rectTemp2.left = m_MouseRect.left + m_2x - 2;
			rectTemp2.right = m_MouseRect.left + m_2x + 2;
			rectTemp2.top = 255 + m_MouseRect.top - m_2y - 2;
			rectTemp2.bottom = 255 + m_MouseRect.top - m_2y + 2;

			// 判断用户在点1或点2旁边
			if ((rectTemp1.PtInRect(point)) || (rectTemp2.PtInRect(point)))
			{

				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}



	// 默认鼠标移动处理事件

	CDialog::OnMouseMove(nFlags, point);

}

int GrayStretch1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lLineBytes, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
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
		// 判断bX1是否等于bX2（防止分母为0）
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

	return 1;

}


void Lashen::OnPaint()
{
	// 字符串

	CString str;
	// 设备上下文

	CPaintDC dc(this);

	// 获取绘制坐标的文本框

	CWnd* pWnd = GetDlgItem(IDC_STATIC);

	// 指针

	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0, 0, 330, 300);

	// 创建画笔对象

	CPen* pPenRed = new CPen;
	// 红色画笔

	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 100, 100));
	// 创建画笔对象
	CPen* pPenBlue = new CPen;
	// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 255, 255));

	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// 绘制坐标轴
	pDC->MoveTo(10, 10);
	// 垂直轴
	pDC->LineTo(10, 280);
	// 水平轴
	pDC->LineTo(320, 280);
// 写坐标
	str.Format(L"0");
	pDC->TextOut(10, 281, str);
	str.Format(L"255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	// 绘制X轴箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	// 绘制X轴箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);



	// 绘制坐标值
	str.Format(L"(%d, %d)", m_1x, m_1y);
	pDC->TextOut(m_1x + 10, 281 - m_1y, str);
	str.Format(L"(%d, %d)", m_2x, m_2y);
	pDC->TextOut(m_2x + 10, 281 - m_2y, str);


	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_1x + 10, 280 - m_1y);
	pDC->LineTo(m_2x + 10, 280 - m_2y);
	pDC->LineTo(265, 25);

	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0, 255, 0));

	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);
	// 绘制小矩形
	pDC->Rectangle(m_1x + 10 - 2, 280 - m_1y - 2, m_1x + 12, 280 - m_1y + 2);
	pDC->Rectangle(m_2x + 10 - 2, 280 - m_2y - 2, m_2x + 12, 280 - m_2y + 2);
	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);
	// 绘制边缘
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);
	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
}

//预览图像
void Lashen::OnBnClickedButton1()
{
	// 获取用户的设定
	BYTE	bX1;
	BYTE	bY1;
	// 点2坐标
	BYTE	bX2;
	BYTE	bY2;
	bX1 = m_1x;
	bY1 = m_1y;
	bX2 = m_2x;
	bY2 = m_2y;
	if (!lpSrcDib) return; 
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);// 获取图象的高度		
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * 8);	// 计算图象每行的字节数
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);//图像像素
	lLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);
	// 更改光标形状
	//BeginWaitCursor();
	// 调用GrayStretch()函数进行灰度拉伸
	GrayStretch1(lpSrcStartBits, lSrcWidth, lSrcHeight, lLineBytes, bX1, bY1, bX2, bY2);
	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
}

//恢复图片
void Lashen::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 恢复图片,将原图片数据拷贝给现在的图片
	for (int i = 0; i < lSrcHeight; i++) {
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
