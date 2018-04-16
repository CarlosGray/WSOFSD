// ResTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "WSOFSD.h"
#include "ResTreeView.h"


// CResTreeView

IMPLEMENT_DYNCREATE(CResTreeView, CFormView)

CResTreeView::CResTreeView()
	: CFormView(IDD_RES_DLG)
{

}

CResTreeView::~CResTreeView()
{
}

void CResTreeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
}

BEGIN_MESSAGE_MAP(CResTreeView, CFormView)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TREE1, &CResTreeView::OnNMCustomdrawTree1)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, &CResTreeView::OnTvnItemexpandedTree1)
END_MESSAGE_MAP()


// CResTreeView 诊断

#ifdef _DEBUG
void CResTreeView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CResTreeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CResTreeView 消息处理程序


void CResTreeView::AddSubNode(CString Path, HTREEITEM parentItem)
{
	CFileFind ff;
	Path.Append(_T("\\*.*"));
	BOOL res = ff.FindFile(Path);
	while (res)
	{
		res = ff.FindNextFile();
		if (!ff.IsSystem() && !ff.IsDots() && ff.IsDirectory())
			m_TreeCtrl.InsertItem(ff.GetFileName(), 0, 0, parentItem);
	}
	ff.Close();
}

void CResTreeView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_TreeRoot = m_TreeCtrl.InsertItem(_T("计算机"));
	HTREEITEM treeTemp = NULL;
	CString path;

	size_t szAllDriveStrinngs = GetLogicalDriveStrings(0, NULL);			//驱动器总长度
	TCHAR *pDriveStrings = new TCHAR[szAllDriveStrinngs + sizeof(_T(""))];	//建立数组
	TCHAR *pTemp = pDriveStrings;
	GetLogicalDriveStrings(szAllDriveStrinngs, pTemp);
	size_t szDriveString = _tcslen(pTemp);									//驱动器大小
	while (szDriveString > 0)
	{
		path = pTemp;
		path.TrimRight(_T("\\"));
		treeTemp = m_TreeCtrl.InsertItem(path, 0, 0, m_TreeRoot);
		AddSubNode(path, treeTemp);
		pTemp += szDriveString + 1;
		szDriveString = _tcslen(pTemp);
	}
	delete[]pDriveStrings;

	LOGFONT logFont;
	GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(logFont), &logFont);
	logFont.lfCharSet = GB2312_CHARSET;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfHeight = 19;
	lstrcpy(logFont.lfFaceName, _T("微软雅黑"));
	m_Font.CreateFontIndirect(&logFont);

	m_TreeCtrl.SetFont(&m_Font);
	m_TreeCtrl.Expand(m_TreeRoot, TVE_EXPAND);
}


void CResTreeView::OnNMCustomdrawTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVCUSTOMDRAW pDraw = reinterpret_cast<LPNMTVCUSTOMDRAW>(pNMHDR);
	NMCUSTOMDRAW nmCustomDraw = pDraw->nmcd;
	switch (nmCustomDraw.dwDrawStage)
	{
	case CDDS_ITEMPREPAINT:
		if (nmCustomDraw.uItemState & CDIS_SELECTED)
		{
			pDraw->clrTextBk = RGB(30, 144, 255);
			pDraw->clrText = RGB(255, 255, 255);
		}
		break;
	}
	*pResult = 0;
	*pResult |= CDRF_NOTIFYPOSTPAINT;
	*pResult |= CDRF_NOTIFYITEMDRAW;
}


void CResTreeView::OnTvnItemexpandedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hExpandedItem = pNMTreeView->itemNew.hItem;
	if (m_TreeRoot == hExpandedItem || m_TreeCtrl.GetItemData(hExpandedItem) == 1)
		return;
	CString SubPath;
	CString CurPath = m_TreeCtrl.GetItemText(hExpandedItem);
	HTREEITEM hTreeItem = m_TreeCtrl.GetParentItem(hExpandedItem);
	while (hTreeItem != m_TreeRoot)
	{
		CurPath = m_TreeCtrl.GetItemText(hTreeItem) + _T("\\") + CurPath;
		hTreeItem = m_TreeCtrl.GetParentItem(hTreeItem);
	}
	hTreeItem = m_TreeCtrl.GetNextItem(hExpandedItem, TVGN_CHILD);
	while (hTreeItem)
	{
		SubPath = CurPath + _T("\\") + m_TreeCtrl.GetItemText(hTreeItem);
		AddSubNode(SubPath, hTreeItem);
		hTreeItem = m_TreeCtrl.GetNextItem(hTreeItem, TVGN_NEXT);
	}
	m_TreeCtrl.SetItemData(hExpandedItem, 1);

	*pResult = 0;
}
