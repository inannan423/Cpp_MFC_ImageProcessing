// CDlgErosion.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "CDlgErosion.h"


// CDlgErosion 对话框

IMPLEMENT_DYNAMIC(CDlgErosion, CDialogEx)

CDlgErosion::CDlgErosion(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nMode1(-1)
	, m_nMode2(-1)
	, m_nstru1(-1)
	, m_nstru2(-1)
	, m_nstru3(-1)
	, m_nstru4(-1)
	, m_nstru5(-1)
	, m_nstru6(-1)
	, m_nstru7(-1)
	, m_nstru8(-1)
	, m_nstru9(-1)
{

}

CDlgErosion::~CDlgErosion()
{
}

void CDlgErosion::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nMode1);
	DDX_Radio(pDX, IDC_RADIO7, m_nMode2);
	DDX_Control(pDX, IDC_RADIO10, m_control1);
	DDX_Control(pDX, IDC_RADIO11, m_control2);
	DDX_Control(pDX, IDC_RADIO12, m_control3);
	DDX_Control(pDX, IDC_RADIO13, m_control4);
	DDX_Control(pDX, IDC_RADIO14, m_control5);
	DDX_Control(pDX, IDC_RADIO15, m_control6);
	DDX_Control(pDX, IDC_RADIO16, m_control7);
	DDX_Control(pDX, IDC_RADIO17, m_control8);
	DDX_Control(pDX, IDC_RADIO18, m_control9);
	DDX_Radio(pDX, IDC_RADIO10, m_nstru1);
	DDX_Radio(pDX, IDC_RADIO11, m_nstru2);
	DDX_Radio(pDX, IDC_RADIO12, m_nstru3);
	DDX_Radio(pDX, IDC_RADIO13, m_nstru4);
	DDX_Radio(pDX, IDC_RADIO14, m_nstru5);
	DDX_Radio(pDX, IDC_RADIO15, m_nstru6);
	DDX_Radio(pDX, IDC_RADIO16, m_nstru7);
	DDX_Radio(pDX, IDC_RADIO17, m_nstru8);
	DDX_Radio(pDX, IDC_RADIO18, m_nstru9);
}


BEGIN_MESSAGE_MAP(CDlgErosion, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO7, &CDlgErosion::OnBnClickedRadio7)
//	ON_BN_CLICKED(IDC_RADIO8, &CDlgErosion::OnBnClickedRadio8)
//	ON_BN_CLICKED(IDC_RADIO9, &CDlgErosion::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CDlgErosion::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO11, &CDlgErosion::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &CDlgErosion::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CDlgErosion::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CDlgErosion::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO15, &CDlgErosion::OnBnClickedRadio15)
	ON_BN_CLICKED(IDC_RADIO16, &CDlgErosion::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO17, &CDlgErosion::OnBnClickedRadio17)
	ON_BN_CLICKED(IDC_RADIO18, &CDlgErosion::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgErosion::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgErosion::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgErosion::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDlgErosion::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CDlgErosion::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CDlgErosion::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO8, &CDlgErosion::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CDlgErosion::OnBnClickedRadio9)
END_MESSAGE_MAP()


// CDlgErosion 消息处理程序


void CDlgErosion::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	//这里是用户选择水平方向后
	//用户选择“自定义”的时候3*3结构元素禁止输入
	m_control1.EnableWindow(FALSE);
	m_control2.EnableWindow(FALSE);
	m_control3.EnableWindow(FALSE);
	m_control4.EnableWindow(FALSE);
	m_control5.EnableWindow(FALSE);
	m_control6.EnableWindow(FALSE);
	m_control7.EnableWindow(FALSE);
	m_control8.EnableWindow(FALSE);
	m_control9.EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(true);//这里标明是水平那三个点点
	((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(false);
	m_nstru1 = 0;
	m_nstru2 = 0;
	m_nstru3 = 0;
	m_nstru4 = 1;
	m_nstru5 = 1;
	m_nstru6 = 1;
	m_nstru7 = 0;
	m_nstru8 = 0;
	m_nstru9 = 0;
	//m_nMode1 = 0;
	//m_nMode2 = 0;
	m_nMode2 = 0;
}



BOOL CDlgErosion::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//这里是打开对话框初始的状态
	// TODO:  在此添加额外的初始化
	m_control1.EnableWindow(FALSE);
	m_control2.EnableWindow(FALSE);
	m_control3.EnableWindow(FALSE);
	m_control4.EnableWindow(FALSE);
	m_control5.EnableWindow(FALSE);
	m_control6.EnableWindow(FALSE);
	m_control7.EnableWindow(FALSE);
	m_control8.EnableWindow(FALSE);
	m_control9.EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(false);

	m_nstru1 = 0;
	m_nstru2 = 0;
	m_nstru3 = 0;
	m_nstru4 = 1;
	m_nstru5 = 1;
	m_nstru6 = 1;
	m_nstru7 = 0;
	m_nstru8 = 0;
	m_nstru9 = 0;
	m_nMode1 = 1;
	m_nMode2 = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgErosion::OnBnClickedRadio10()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru1 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(true);
		m_nstru1 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(false);
		m_nstru1 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio11()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru2 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(true);
		m_nstru2 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(false);
		m_nstru2 = 0;
	}
}

//这里就是说明你点了这个按钮之后对应的变量变为1
void CDlgErosion::OnBnClickedRadio12()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru3 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(true);
		m_nstru3 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(false);
		m_nstru3= 0;
	}
}


void CDlgErosion::OnBnClickedRadio13()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru4 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(true);
		m_nstru4 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(false);
		m_nstru4 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio14()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru5 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(true);
		m_nstru5 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(false);
		m_nstru5 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio15()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru6 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(true);
		m_nstru6 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(false);
		m_nstru6 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio16()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru7 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(true);
		m_nstru7 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(false);
		m_nstru7 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio17()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru8 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(true);
		m_nstru8 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(false);
		m_nstru8 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio18()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nstru9 == 0) {
		((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(true);
		m_nstru9 = 1;
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(false);
		m_nstru9 = 0;
	}
}


void CDlgErosion::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 1;
}


void CDlgErosion::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 2;
}


void CDlgErosion::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 3;
}


void CDlgErosion::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 4;
}


void CDlgErosion::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 5;
}


void CDlgErosion::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMode1 = 6;
}


void CDlgErosion::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control1.EnableWindow(FALSE);
	m_control2.EnableWindow(FALSE);
	m_control3.EnableWindow(FALSE);
	m_control4.EnableWindow(FALSE);
	m_control5.EnableWindow(FALSE);
	m_control6.EnableWindow(FALSE);
	m_control7.EnableWindow(FALSE);
	m_control8.EnableWindow(FALSE);
	m_control9.EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(false);
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(true);
	((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(false);
	m_nstru1 = 0;
	m_nstru2 = 1;
	m_nstru3 = 0;
	m_nstru4 = 0;
	m_nstru5 = 1;
	m_nstru6 = 0;
	m_nstru7 = 0;
	m_nstru8 = 1;
	m_nstru9 = 0;
	m_nMode2 = 1;
}


void CDlgErosion::OnBnClickedRadio9()
{
	// TODO: 在此添加控件通知处理程序代码
	m_control1.EnableWindow(TRUE);
	m_control2.EnableWindow(TRUE);
	m_control3.EnableWindow(TRUE);
	m_control4.EnableWindow(TRUE);
	m_control5.EnableWindow(TRUE);
	m_control6.EnableWindow(TRUE);
	m_control7.EnableWindow(TRUE);
	m_control8.EnableWindow(TRUE);
	m_control9.EnableWindow(TRUE);

	m_nMode2 = 2;
}
