// Lvjing.cpp: 实现文件
//

#include "pch.h"
#include "MFCTemplate.h"
#include "afxdialogex.h"
#include "Lvjing.h"


// Lvjing 对话框

IMPLEMENT_DYNAMIC(Lvjing, CDialogEx)

Lvjing::Lvjing(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Lvj, pParent)
	, m_operator1(0)
	, m_operator2(0)
	, m_operator3(0)
	, m_operator4(0)
	, m_operator5(0)
	, m_operator6(0)
	, m_operator7(0)
	, m_operator8(0)
	, m_operator9(0)
	, m_coefficient(0)
	, m_constant(0)
	, m_filter_species(0)
	, m_edge_direction(0)
{

}

Lvjing::~Lvjing()
{
}

void Lvjing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_operator1);
	DDX_Text(pDX, IDC_EDIT2, m_operator2);
	DDX_Text(pDX, IDC_EDIT3, m_operator3);
	DDX_Text(pDX, IDC_EDIT4, m_operator4);
	DDX_Text(pDX, IDC_EDIT5, m_operator5);
	DDX_Text(pDX, IDC_EDIT6, m_operator6);
	DDX_Text(pDX, IDC_EDIT7, m_operator7);
	DDX_Text(pDX, IDC_EDIT8, m_operator8);
	DDX_Text(pDX, IDC_EDIT9, m_operator9);
	DDX_Text(pDX, IDC_EDIT10, m_coefficient);
	DDX_Text(pDX, IDC_EDIT11, m_constant);
	DDX_Control(pDX, IDC_RADIO1, m_filter1_Control);
	DDX_Radio(pDX, IDC_RADIO1, m_filter_species);
	DDX_Control(pDX, IDC_RADIOsp, m_filter8_Control);
	DDX_Radio(pDX, IDC_RADIOsp, m_edge_direction);
	DDX_Control(pDX, IDC_EDIT1, suanzi1);
	DDX_Control(pDX, IDC_EDIT2, suanzi2);
	DDX_Control(pDX, IDC_EDIT3, suanzi3);
	DDX_Control(pDX, IDC_EDIT4, suanzi4);
	DDX_Control(pDX, IDC_EDIT5, suanzi5);
	DDX_Control(pDX, IDC_EDIT6, suanzi6);
	DDX_Control(pDX, IDC_EDIT7, suanzi7);
	DDX_Control(pDX, IDC_EDIT8, suanzi8);
	DDX_Control(pDX, IDC_EDIT9, suanzi9);
	DDX_Control(pDX, IDC_EDIT10, suanzi10);
	DDX_Control(pDX, IDC_EDIT11, suanzi11);
	DDX_Control(pDX, IDC_suanzi, suanz);
	DDX_Control(pDX, IDC_light, clicklight);
}


BEGIN_MESSAGE_MAP(Lvjing, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Lvjing::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Lvjing::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Lvjing::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Lvjing::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_RADIO1, &Lvjing::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIOsp, &Lvjing::OnBnClickedRadiosp)
	ON_BN_CLICKED(IDC_RADIO2, &Lvjing::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Lvjing::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIOrh, &Lvjing::OnBnClickedRadiorh)
	ON_BN_CLICKED(IDC_RADIOfd, &Lvjing::OnBnClickedRadiofd)
	ON_BN_CLICKED(IDC_RADIOsob, &Lvjing::OnBnClickedRadiosob)
	ON_BN_CLICKED(IDC_RADIOp, &Lvjing::OnBnClickedRadiop)
	ON_BN_CLICKED(IDC_RADIOcz, &Lvjing::OnBnClickedRadiocz)
	ON_BN_CLICKED(IDC_suanzi, &Lvjing::OnBnClickedsuanzi)
	ON_BN_CLICKED(IDC_light, &Lvjing::OnBnClickedlight)
END_MESSAGE_MAP()


// Lvjing 消息处理程序
int M = 0;
int lt = 0;
int with_edge = 0;
void Lvjing::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString gReadFilePathName1;
	CFileDialog fileDlg(false, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("txt Files (*.txt)|*.txt|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		gReadFilePathName1 = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名
	}

	delete fileDlg;
	CStdioFile file;
	CString a = L"\n";
	CString strText(_T(""));
	file.Open(gReadFilePathName1, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	GetDlgItemText(IDC_EDIT1, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT2, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT3, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT4, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT5, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT6, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT7, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT8, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT9, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT10, strText);
	strText = strText + a;
	file.WriteString(strText);
	GetDlgItemText(IDC_EDIT11, strText);
	file.WriteString(strText);
	file.Close();
}




void Lvjing::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString gReadFilePathName1;
	CString szFileName;

	CFileDialog dlg(true, _T(".txt"), _T("*.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文件 (*.txt)|*.txt||"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		szFileName = dlg.GetPathName();
	}
	CString strLine, strTemp, result;
	int row = 0;
	CStdioFile file(szFileName, CFile::modeRead);
	CString line[12];
	while (file.ReadString(strLine))
	{
		char* str = (char*)strLine.GetBufferSetLength(strLine.GetLength());
		if (strLine != "")
		{
			line[row] = strLine;
			row++;
		}
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(line[0]);
	GetDlgItem(IDC_EDIT2)->SetWindowText(line[1]);
	GetDlgItem(IDC_EDIT3)->SetWindowText(line[2]);
	GetDlgItem(IDC_EDIT4)->SetWindowText(line[3]);
	GetDlgItem(IDC_EDIT5)->SetWindowText(line[4]);
	GetDlgItem(IDC_EDIT6)->SetWindowText(line[5]);
	GetDlgItem(IDC_EDIT7)->SetWindowText(line[6]);
	GetDlgItem(IDC_EDIT8)->SetWindowText(line[7]);
	GetDlgItem(IDC_EDIT9)->SetWindowText(line[8]);
	GetDlgItem(IDC_EDIT10)->SetWindowText(line[9]);
	GetDlgItem(IDC_EDIT11)->SetWindowText(line[10]);
	file.Close();
}


BOOL WINAPI Template_Filter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight,
	int iTempH, int iTempW,
	int iTempMX, int iTempMY,
	FLOAT* Arr, FLOAT fCoef, float threshold)
{
	// 指向复制图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	// 指向源图像的指针
	unsigned char* lpSrc;

	// 指向要复制区域的指针
	unsigned char* lpDst;

	// 循环变量
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;

	// 计算结果
	FLOAT	fResult;
	// 图像每行的字节数
	LONG lLineBytes;
	// 计算图像每行的字节数
	lLineBytes = (lWidth + 3) / 4 * 4;
	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	// 判断是否内存分配失败
	if (hNewDIBBits == NULL)
	{
		// 分配内存失败
		return FALSE;
	}
	// 锁定内存
	lpNewDIBBits = (char*)LocalLock(hNewDIBBits);
	// 初始化图像为原始图像
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	// 行(除去边缘几行)
	for (i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// 列(除去边缘几列)
		for (j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// 指向新DIB第i行，第j个象素的指针
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;

			fResult = 0;

			// 计算
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// 指向DIB第i - iTempMY + k行，第j - iTempMX + l个象素的指针
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;
					// 保存象素值
					fResult += (*lpSrc) * Arr[k * iTempW + l];
				}
			}
			// 乘上系数
			fResult *= fCoef;
			//加上常数
			fResult += threshold;
			//取绝对值
			fResult = (FLOAT)fabs(fResult);

			if (fResult > 255)
			{
				*lpDst = 255;
			}
			else
			{
				*lpDst = (unsigned char)(fResult + 0.5);
			}
		}
	}
	// 复制变换后的图像
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// 返回
	return TRUE;

}



void Lvjing::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_filter8_Control.EnableWindow(false);
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_operator1 = 0;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 1;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = -1;
	m_constant = 255;
	
	m_filter_species = 0;
	UpdateData(false);
}


void Lvjing::OnBnClickedRadiosp()
{
	// TODO: 在此添加控件通知处理程序代码
	if (with_edge == 0)//sobel
	{
		m_operator1 = -1;
		m_operator2 = 0;
		m_operator3 = 1;
		m_operator4 = -2;
		m_operator5 = 0;
		m_operator6 = 2;
		m_operator7 = -1;
		m_operator8 = 0;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		
		m_filter_species = 5;
		m_edge_direction = 0;
		UpdateData(false);
	}
	if (with_edge == 1)//prewitt
	{
		m_operator1 = -1;
		m_operator2 = 0;
		m_operator3 = 1;
		m_operator4 = -1;
		m_operator5 = 0;
		m_operator6 = 1;
		m_operator7 = -1;
		m_operator8 = 0;
		m_operator9 = 1;
		m_coefficient = 1.0;
		m_constant = 0;

		
		m_filter_species = 6;
		m_edge_direction = 0;
		UpdateData(false);
	}
}


void Lvjing::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_filter8_Control.EnableWindow(false);
	m_operator1 = 1;
	m_operator2 = 1;
	m_operator3 = 1;
	m_operator4 = 1;
	m_operator5 = 1;
	m_operator6 = 1;
	m_operator7 = 1;
	m_operator8 = 1;
	m_operator9 = 1;
	m_coefficient = 1.0 / 9.0;
	m_constant = 0;
	
	m_filter_species = 1;
	UpdateData(false);
}


void Lvjing::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_filter8_Control.EnableWindow(false);
	m_operator1 = 1;
	m_operator2 = 2;
	m_operator3 = 1;
	m_operator4 = 2;
	m_operator5 = 4;
	m_operator6 = 2;
	m_operator7 = 1;
	m_operator8 = 2;
	m_operator9 = 1;
	m_coefficient = 1.0 / 16.0;
	m_constant = 0;
	
	m_filter_species = 2;
	UpdateData(false);
}


void Lvjing::OnBnClickedRadiorh()
{
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_filter8_Control.EnableWindow(false);
	m_operator1 = -1;
	m_operator2 = -1;
	m_operator3 = -1;
	m_operator4 = -1;
	m_operator5 = 8;
	m_operator6 = -1;
	m_operator7 = -1;
	m_operator8 = -1;
	m_operator9 = -1;
	m_coefficient = 1.0;///9.0;   
	m_constant = 0;
	
	m_filter_species = 3;
	UpdateData(false);
}



void Lvjing::OnBnClickedRadiofd()
{
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_filter8_Control.EnableWindow(false);
	m_operator1 = 1;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 0;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = -1;
	m_coefficient = 1.0;
	m_constant = 128;
	
	m_filter_species = 4;
	UpdateData(false);
}


void Lvjing::OnBnClickedRadiosob()
{
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	m_filter8_Control.EnableWindow(true);
	m_filter8_Control.SetCheck(false);
	with_edge = 0;//sobel
}





void Lvjing::OnBnClickedRadiop()
{
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	// TODO: 在此添加控件通知处理程序代码
	m_filter8_Control.EnableWindow(true);
	m_filter8_Control.SetCheck(false);
	with_edge = 1;//prewitt
}



void Lvjing::OnBnClickedRadiocz()
{
	// TODO: 在此添加控件通知处理程序代码
	if (with_edge == 0)//sobel
	{
		m_operator1 = 1;
		m_operator2 = 2;
		m_operator3 = 1;
		m_operator4 = 0;
		m_operator5 = 0;
		m_operator6 = 0;
		m_operator7 = -1;
		m_operator8 = -2;
		m_operator9 = -1;
		m_coefficient = 1.0;
		m_constant = 0;

		
		m_filter_species = 5;
		m_edge_direction = 1;
		UpdateData(false);
	}


	if (with_edge == 1)//水平
	{
		m_operator1 = 1;
		m_operator2 = 1;
		m_operator3 = 1;
		m_operator4 = 0;
		m_operator5 = 0;
		m_operator6 = 0;
		m_operator7 = -1;
		m_operator8 = -1;
		m_operator9 = -1;
		m_coefficient = 1.0;
		m_constant = 0;

		
		m_filter_species = 6;
		m_edge_direction = 1;
		UpdateData(false);
	}
}



void Lvjing::OnBnClickedsuanzi()
{
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(true);
	suanzi2.EnableWindow(true);
	suanzi3.EnableWindow(true);
	suanzi4.EnableWindow(true);
	suanzi5.EnableWindow(true);
	suanzi6.EnableWindow(true);
	suanzi7.EnableWindow(true);
	suanzi8.EnableWindow(true);
	suanzi9.EnableWindow(true);
	suanzi10.EnableWindow(true);
	suanzi11.EnableWindow(true);
	suanz.EnableWindow(true);
	m_filter8_Control.EnableWindow(false);
	m_operator1 = 0;
	m_operator2 =0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 0;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = 1.0;///9.0;   
	m_constant = 0;
	//UpdateData(false);
	//m_filter_species = 3;
	//m_filter_species = 7;
	//UpdateData(false);
}

void Lvjing::OnBnClickedlight()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(true);
	clicklight.EnableWindow(true);
	clicklight.SetCheck(true);
	

	m_operator1 = 0;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 0;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = 99.9;///9.0;   
	m_constant = 0;
	M = 1;
	m_filter1_Control.SetCheck(false);
	UpdateData(false);
}

BOOL Lvjing::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	suanzi1.EnableWindow(false);
	suanzi2.EnableWindow(false);
	suanzi3.EnableWindow(false);
	suanzi4.EnableWindow(false);
	suanzi5.EnableWindow(false);
	suanzi6.EnableWindow(false);
	suanzi7.EnableWindow(false);
	suanzi8.EnableWindow(false);
	suanzi9.EnableWindow(false);
	suanzi10.EnableWindow(false);
	suanzi11.EnableWindow(false);
	m_filter1_Control.SetCheck(true);

	m_operator1 = 0;
	m_operator2 = 0;
	m_operator3 = 0;
	m_operator4 = 0;
	m_operator5 = 1;
	m_operator6 = 0;
	m_operator7 = 0;
	m_operator8 = 0;
	m_operator9 = 0;
	m_coefficient = -1;
	m_constant = 255;

	m_filter_species = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}







//预览图片
void Lvjing::OnBnClickedButton3()
{
	//预览图片
	//模板高度
	int iTempH;
	//模板宽度
	int iTempW;
	//模板系数
	//FLOAT fTempC;
	//模板中心元素X坐标
	int iTempMX;
	//模板中心元素Y坐标
	int iTempMY;
	//模板元素数组
	FLOAT aValue[9];
	float coefficient;
	int constant;


	// 设定平移量（3*3）
	iTempH = 3;
	iTempW = 3;
	iTempMX = 2;
	iTempMY = 2;

	aValue[0] = m_operator1;
	aValue[1] = m_operator2;
	aValue[2] = m_operator3;
	aValue[3] = m_operator4;
	aValue[4] = m_operator5;
	aValue[5] = m_operator6;
	aValue[6] = m_operator7;
	aValue[7] = m_operator8;
	aValue[8] = m_operator9;
	coefficient = m_coefficient;
	constant = m_constant;
	unsigned char* lpSrcData = 0;
	CString strInfo;
	strInfo.Format(_T("%d"), constant);
	//MessageBox(0, strInfo, NULL);
	if (M == 1) {
		int page = 1;
		if (lpSrcBitCount == 24) page = 3;
		if (lpSrcBitCount == 8) page = 1;
		int changing = constant;
		//std::cout << changing;
		for (int i = 0; i < lSrcHeight; i++) {
			for (int j = 0; j < lSrcWidth; j++) {
				for (int l = 0; l < page; l++) {
					lpSrcData = (unsigned char*)lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j * page + l;
					int temp = *lpSrcData + changing;
					if (temp < 0) {
						*lpSrcData = 0;
					}
					else if (temp > 255) {
						*lpSrcData = 255;
					}
					else {
						*lpSrcData = (unsigned char)(temp + 0.5);
					}
				}

			}
		}
		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);
		// 更新视图
		pDoc->UpdateAllViews(NULL);
		UpdateData(false);
	}
	else {
		Template_Filter(lpSrcStartBits, lSrcWidth, lSrcHeight,
			iTempH, iTempW, iTempMX, iTempMY, aValue, coefficient, constant);

		// 设置脏标记
		pDoc->SetModifiedFlag(TRUE);

		// 更新视图
		pDoc->UpdateAllViews(NULL);
		UpdateData(false);

	}
	
}


void Lvjing::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 1; i < lSrcHeight - 1; i++)
		for (int j = 1; j < lSrcWidth - 1; j++)
		{
			lpSrcStartBits[i * lSrcWidth + j] = beginBits[i * lSrcWidth + j];
		}

	// 设置脏标记 
	pDoc->SetModifiedFlag(false);

	// 更新视图
	pDoc->UpdateAllViews(NULL);
	UpdateData(false);
}

