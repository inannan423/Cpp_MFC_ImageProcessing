// Move.cpp: 实现文件
//
#include "stdafx.h"
//#include "pch.h"
#include "MFCTemplate.h"
#include "Move.h"
#include "afxdialogex.h"


// Move 对话框

IMPLEMENT_DYNAMIC(Move, CDialogEx)

Move::Move(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Move, pParent)
	, MoveX(0)
	, MoveY(0)
{

}

Move::~Move()
{
}

void Move::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, MoveX);
	DDX_Text(pDX, IDC_EDIT2, MoveY);
}


BEGIN_MESSAGE_MAP(Move, CDialogEx)
END_MESSAGE_MAP()


// Move 消息处理程序
