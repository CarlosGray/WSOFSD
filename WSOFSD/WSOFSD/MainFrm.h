
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	
// ����
public:
	CSplitterWnd m_wndSplitter;
	CView *m_pTaskView;
	CView *m_pMainView;
	bool m_IsShowTask;
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


