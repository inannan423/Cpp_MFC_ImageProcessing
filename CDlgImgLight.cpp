// CDlgImgLight.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "CDlgImgLight.h"


// CDlgImgLight 对话框

IMPLEMENT_DYNAMIC(CDlgImgLight, CDialogEx)

CDlgImgLight::CDlgImgLight(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_InputChanglight, pParent)
	, Lightness(0)
{

}

CDlgImgLight::~CDlgImgLight()
{
}

void CDlgImgLight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BoxInput, Lightness);
}


BEGIN_MESSAGE_MAP(CDlgImgLight, CDialogEx)
END_MESSAGE_MAP()


// CDlgImgLight 消息处理程序


BOOL CDlgImgLight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
