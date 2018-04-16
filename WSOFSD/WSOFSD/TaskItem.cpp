// TaskItem.cpp : 实现文件
//

#include "stdafx.h"
#include "WSOFSD.h"
#include "TaskItem.h"
#include "afxdialogex.h"

// CTaskItem 对话框

IMPLEMENT_DYNAMIC(CTaskItem, CDialogEx)

CTaskItem::CTaskItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent), m_iMax(100),m_iMin(0),m_iPos(0),m_nBarWidth(0),m_prgsColor(RGB(122, 196, 255)),m_Fraction(0.0), m_iOutNum(0)
{
	m_hTaskIcon = ::LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
}

CTaskItem::~CTaskItem()
{
}

void CTaskItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_PIC, m_Pic);
	DDX_Control(pDX, IDC_PROGRESS_INFO, m_ProTips);
}


BEGIN_MESSAGE_MAP(CTaskItem, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTaskItem 消息处理程序


int CTaskItem::SetPos(int nPos)
{
	if (!::IsWindow(m_hWnd) || m_iPos > m_iMax)
		return -1;
	int nOldPos = m_iPos;
	m_iPos = nPos;
	CRect rect;
	GetClientRect(&rect);
	m_Fraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
	int nBarWidth = (int)(m_Fraction * rect.Width());
	if (nBarWidth != m_nBarWidth)
	{
		m_nBarWidth = nBarWidth;
		RedrawWindow();
	}

	return nOldPos;
}

BOOL CTaskItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 100, NULL);

	SetBackgroundColor(RGB(237, 244, 249));
	LOGFONT logFont;
	GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(logFont), &logFont);
	logFont.lfCharSet = GB2312_CHARSET;
	logFont.lfWeight = FW_NORMAL;
	logFont.lfHeight = 19;
	lstrcpy(logFont.lfFaceName, _T("微软雅黑"));
	m_Font.CreateFontIndirect(&logFont);

	m_ProTips.SetFont((&m_Font));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


HBRUSH CTaskItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC || OCM_CTLCOLORBTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		return HBRUSH(GetStockObject(NULL_BRUSH));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTaskItem::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect LeftRect, CLientRect;
	GetClientRect(CLientRect);
	LeftRect = CLientRect;

	LeftRect.right = LeftRect.left + m_nBarWidth;
	dc.FillSolidRect(LeftRect, m_prgsColor);

	CRect PicRect;
	m_Pic.GetWindowRect(PicRect);
	ScreenToClient(PicRect);
	::DrawIconEx(dc, PicRect.left, PicRect.top, m_hTaskIcon, 32, 32, 0, NULL, DI_NORMAL | DI_COMPAT);
}


void CTaskItem::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_iOutNum > m_iMax)
		return;
	m_ProInfo.Format(_T("%d%%"), (int)(m_Fraction * 100));
	m_ProTips.SetWindowTextW(m_ProInfo);
	SetPos(++m_iOutNum);
	CDialogEx::OnTimer(nIDEvent);
}
