#pragma once


// Move 对话框

class Move : public CDialogEx
{
	DECLARE_DYNAMIC(Move)

public:
	Move(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Move();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Move };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	long MoveX;
	long MoveY;
};
