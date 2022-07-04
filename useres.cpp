// useres.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCTemplate.h"
#include "useres.h"
#include "afxdialogex.h"


// useres 对话框

IMPLEMENT_DYNAMIC(useres, CDialogEx)

useres::useres(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_res, pParent)
	, m_Num(0)
	, m_mSquare(0)
	, m_mCmeter(0)
	, m_circle(0)
	, m_square(0)
	, m_x(0)
	, m_y(0)
{

}

useres::~useres()
{
}

void useres::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Num);
	DDX_Text(pDX, IDC_EDIT2, m_mSquare);
	DDX_Text(pDX, IDC_EDIT3, m_mCmeter);
	DDX_Text(pDX, IDC_EDIT4, m_circle);
	DDX_Text(pDX, IDC_EDIT5, m_square);
	DDX_Text(pDX, IDC_EDIT6, m_x);
	DDX_Text(pDX, IDC_EDIT7, m_y);
}


BEGIN_MESSAGE_MAP(useres, CDialogEx)
END_MESSAGE_MAP()


// useres 消息处理程序
