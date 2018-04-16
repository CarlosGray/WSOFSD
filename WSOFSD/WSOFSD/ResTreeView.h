#pragma once
#include "afxcmn.h"



// CResTreeView ������ͼ

class CResTreeView : public CFormView
{
	DECLARE_DYNCREATE(CResTreeView)

protected:
	CResTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CResTreeView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RES_DLG };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeCtrl;
	HTREEITEM m_TreeRoot;
	CFont m_Font;


	void AddSubNode(CString Path, HTREEITEM parentItem);
	virtual void OnInitialUpdate();
	afx_msg void OnNMCustomdrawTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnItemexpandedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};


