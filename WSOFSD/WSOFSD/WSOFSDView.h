
// WSOFSDView.h : CWSOFSDView ��Ľӿ�
//

#pragma once
#include <list>
#include "TaskItem.h"

static UINT NEAR WM_ADD_ITEM_MSG = RegisterWindowMessage(_T("AddItemMsg"));
class CWSOFSDView : public CFormView
{
protected: // �������л�����
	CWSOFSDView();
	DECLARE_DYNCREATE(CWSOFSDView)

// ����
public:
	CWSOFSDDoc* GetDocument() const;
// ����
public:
	int m_CurIndex;
	CSize m_size;
	std::list<CTaskItem*> m_ItemList;

	HACCEL m_hAccel;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CWSOFSDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // WSOFSDView.cpp �еĵ��԰汾
inline CWSOFSDDoc* CWSOFSDView::GetDocument() const
   { return reinterpret_cast<CWSOFSDDoc*>(m_pDocument); }
#endif

