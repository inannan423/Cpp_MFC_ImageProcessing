// ChangeFile.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "ChangeFile.h"


// ChangeFile 对话框

IMPLEMENT_DYNAMIC(ChangeFile, CDialogEx)

ChangeFile::ChangeFile(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ChangeFile, pParent)
{

}

ChangeFile::~ChangeFile()
{
}

void ChangeFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangeFile, CDialogEx)
END_MESSAGE_MAP()


// ChangeFile 消息处理程序


BOOL ChangeFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
