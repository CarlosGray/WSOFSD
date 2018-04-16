
// WSOFSDView.cpp : CWSOFSDView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "WSOFSD.h"
#endif
#include "OSConfig.h"
#include "WSOFSDDoc.h"
#include "WSOFSDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LAYOUT_OFFSET 6
#define ITEM_HEIGHT 48
// CWSOFSDView

IMPLEMENT_DYNCREATE(CWSOFSDView, CFormView)

BEGIN_MESSAGE_MAP(CWSOFSDView, CFormView)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CWSOFSDView 构造/析构

CWSOFSDView::CWSOFSDView()
	:CFormView(IDD_TASKLIST_VIEW), m_CurIndex(0)
{
	// TODO: 在此处添加构造代码
}

CWSOFSDView::~CWSOFSDView()
{
}

BOOL CWSOFSDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	return CView::PreCreateWindow(cs);
}

// CWSOFSDView 绘制

void CWSOFSDView::OnDraw(CDC* /*pDC*/)
{
	CWSOFSDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CWSOFSDView 诊断

#ifdef _DEBUG
void CWSOFSDView::AssertValid() const
{
	CView::AssertValid();
}

void CWSOFSDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWSOFSDDoc* CWSOFSDView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWSOFSDDoc)));
	return (CWSOFSDDoc*)m_pDocument;
}
#endif //_DEBUG


// CWSOFSDView 消息处理程序

LRESULT CWSOFSDView::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	UINT Mod = (UINT)LOWORD(lParam); // key-modifier flags 
	UINT uVirtKey = (UINT)HIWORD(lParam); // virtual-key code 
										  //判断响应了什么热键 
	if (NULL == Mod  && VK_F1 == uVirtKey)
	{
		CRect rect;
		GetClientRect(rect);
		CTaskItem *pItem = new CTaskItem();
		pItem->Create(IDD_ITEM_DLG, this);
		pItem->MoveWindow(CRect(CPoint(LAYOUT_OFFSET, LAYOUT_OFFSET * (m_CurIndex + 1) + m_CurIndex * ITEM_HEIGHT),
			CSize(rect.Width() - 2 * LAYOUT_OFFSET, ITEM_HEIGHT)));
		pItem->ShowWindow(SW_SHOW);

		m_ItemList.push_back(pItem);
		m_CurIndex++;
		m_size.cy = LAYOUT_OFFSET *(m_CurIndex + 1) + (m_CurIndex)* ITEM_HEIGHT;
		SetScrollSizes(MM_TEXT, m_size);

	}
	else if (NULL == Mod  && VK_F2 == uVirtKey)
	{
		COSConfig::GetDesktopPath();
	}
	else
		AfxMessageBox(_T("你按下了未知热键"));
	return 0;
}


void CWSOFSDView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	RegisterHotKey(m_hWnd, ID_HOTKEY, NULL, VK_F1);
	RegisterHotKey(m_hWnd, ID_HOTKEY2, NULL, VK_F2);
}


void CWSOFSDView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	SetScrollSizes(MM_TEXT, m_size);
	// TODO: 在此处添加消息处理程序代码
}
