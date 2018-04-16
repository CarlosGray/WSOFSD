#pragma once
#include "afxwin.h"


// CTaskItem 对话框

class CTaskItem : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskItem)

public:
	CTaskItem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTaskItem();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Pic;
	CStatic m_ProTips;
	CString m_ProInfo;
	CFont m_Font;
	COLORREF m_prgsColor;

	double m_Fraction;
	int m_iMax;
	int m_iMin;
	int m_iPos;
	int m_nBarWidth;

	int m_iOutNum;
	HICON m_hTaskIcon;

	int SetPos(int nPos);
	void SetRange(int nLower, int nUpper) { m_iMin = nLower; m_iMax = nUpper; m_iPos = m_iMin; m_nBarWidth = 0; }
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
