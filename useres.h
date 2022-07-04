#pragma once


// useres 对话框

class useres : public CDialogEx
{
	DECLARE_DYNAMIC(useres)

public:
	useres(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~useres();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_res };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Num;
	int m_mSquare;
	int m_mCmeter;
	double m_circle;
	double m_square;
	int m_x;
	int m_y;
};
