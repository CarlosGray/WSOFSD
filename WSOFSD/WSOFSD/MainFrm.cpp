
// MainFrm.cpp : CMainFrame ���ʵ��
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

// CMainFrame ����/����

CMainFrame::CMainFrame():m_pMainView(NULL),m_pTaskView(NULL), m_IsShowTask(false)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.hMenu = NULL;
	cs.style &= ~(LONG)FWS_ADDTOTITLE;
	m_strTitle = _T("���ĵ��ܽ�");

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	CRect rct;
	GetClientRect(rct);
	int MainViewWidth = rct.Width() - 266;
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CResTreeView), CSize(266, rct.Height()), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CWSOFSDView), CSize(MainViewWidth, rct.Height()), pContext);

	return TRUE;
}
