// yinxie.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "yinxie.h"


// yinxie 对话框

IMPLEMENT_DYNAMIC(yinxie, CDialogEx)

yinxie::yinxie(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

yinxie::~yinxie()
{
}

void yinxie::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, num);
}


BEGIN_MESSAGE_MAP(yinxie, CDialogEx)
END_MESSAGE_MAP()


// yinxie 消息处理程序
