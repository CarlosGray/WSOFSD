
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "WSOFSD.h"
#include "WSOFSDDoc.h"
#include "WSOFSDView.h"
#include "ResTreeView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame():m_pMainView(NULL),m_pTaskView(NULL), m_IsShowTask(false)
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.hMenu = NULL;
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	m_strTitle = _T("单文档总结");

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	CRect rct;
	GetClientRect(rct);
	int MainViewWidth = rct.Width() - 266;
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CResTreeView), CSize(266, rct.Height()), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CWSOFSDView), CSize(MainViewWidth, rct.Height()), pContext);

	return TRUE;
}
