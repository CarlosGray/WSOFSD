
// WSOFSDView.h : CWSOFSDView 类的接口
//

#pragma once
#include <list>
#include "TaskItem.h"

static UINT NEAR WM_ADD_ITEM_MSG = RegisterWindowMessage(_T("AddItemMsg"));
class CWSOFSDView : public CFormView
{
protected: // 仅从序列化创建
	CWSOFSDView();
	DECLARE_DYNCREATE(CWSOFSDView)

// 特性
public:
	CWSOFSDDoc* GetDocument() const;
// 操作
public:
	int m_CurIndex;
	CSize m_size;
	std::list<CTaskItem*> m_ItemList;

	HACCEL m_hAccel;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CWSOFSDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // WSOFSDView.cpp 中的调试版本
inline CWSOFSDDoc* CWSOFSDView::GetDocument() const
   { return reinterpret_cast<CWSOFSDDoc*>(m_pDocument); }
#endif

