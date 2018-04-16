
// WSOFSDView.cpp : CWSOFSDView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CWSOFSDView ����/����

CWSOFSDView::CWSOFSDView()
	:CFormView(IDD_TASKLIST_VIEW), m_CurIndex(0)
{
	// TODO: �ڴ˴���ӹ������
}

CWSOFSDView::~CWSOFSDView()
{
}

BOOL CWSOFSDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

// CWSOFSDView ����

void CWSOFSDView::OnDraw(CDC* /*pDC*/)
{
	CWSOFSDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CWSOFSDView ���

#ifdef _DEBUG
void CWSOFSDView::AssertValid() const
{
	CView::AssertValid();
}

void CWSOFSDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWSOFSDDoc* CWSOFSDView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWSOFSDDoc)));
	return (CWSOFSDDoc*)m_pDocument;
}
#endif //_DEBUG


// CWSOFSDView ��Ϣ�������

LRESULT CWSOFSDView::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	UINT Mod = (UINT)LOWORD(lParam); // key-modifier flags 
	UINT uVirtKey = (UINT)HIWORD(lParam); // virtual-key code 
										  //�ж���Ӧ��ʲô�ȼ� 
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
		AfxMessageBox(_T("�㰴����δ֪�ȼ�"));
	return 0;
}


void CWSOFSDView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	RegisterHotKey(m_hWnd, ID_HOTKEY, NULL, VK_F1);
	RegisterHotKey(m_hWnd, ID_HOTKEY2, NULL, VK_F2);
}


void CWSOFSDView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	SetScrollSizes(MM_TEXT, m_size);
	// TODO: �ڴ˴������Ϣ����������
}
