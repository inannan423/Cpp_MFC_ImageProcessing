// use.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCTemplate.h"
#include "use.h"
#include "afxdialogex.h"


// use 对话框

IMPLEMENT_DYNAMIC(use, CDialogEx)

use::use(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Use, pParent)
{

}

use::~use()
{
}

void use::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(use, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &use::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &use::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &use::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &use::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &use::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_CHECK1, &use::OnBnClickedCheck1)
END_MESSAGE_MAP()


// use 消息处理程序


void use::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 0;
}


void use::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 1;
}


void use::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_foreground = 2;
}


void use::OnBnClickedRadio4()
{
	m_link = 1;
}


void use::OnBnClickedRadio5()
{
	m_link = 0;
}


void use::OnBnClickedCheck1()
{
	m_forecolor = 1;
}
