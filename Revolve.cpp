// Revolve.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "Revolve.h"


// Revolve 对话框

IMPLEMENT_DYNAMIC(Revolve, CDialogEx)

Revolve::Revolve(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	,dushu(90)
{

}

Revolve::~Revolve()
{
}

void Revolve::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT1, dushu);
	//UpdateData(false);
}


BEGIN_MESSAGE_MAP(Revolve, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &Revolve::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Revolve 消息处理程序


void Revolve::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
