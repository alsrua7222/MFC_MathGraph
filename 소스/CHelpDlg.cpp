// CHelpDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CHelpDlg.h"
#include "afxdialogex.h"
#include "Function_1Dlg.h"


// CHelpDlg 대화 상자

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	m_bFirst = false;
	m_nStage = 0;

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_UNDO, m_btnUndo);
	//  DDX_Control(pDX, IDC_BUTTON_REDO, m_btnRedo);
	//  DDX_Control(pDX, IDC_MFCBUTTON_AGO, m_btnAgo);
	//  DDX_Control(pDX, IDC_MFCBUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_AGO, m_btnAgo);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
ON_WM_ERASEBKGND()
ON_WM_PAINT()
ON_BN_CLICKED(IDC_BUTTON_NEXT, &CHelpDlg::OnBnClickedButtonNext)
ON_BN_CLICKED(IDC_BUTTON_AGO, &CHelpDlg::OnBnClickedButtonAgo)
END_MESSAGE_MAP()


// CHelpDlg 메시지 처리기


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rect;
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	pMain->GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());

	GetDlgItem(IDC_BUTTON_NEXT)->GetWindowRect(&m_rectNext);
	ScreenToClient(m_rectNext);
	m_btnAgo.LoadBitmaps(IDB_BITMAP_AGO, NULL, NULL, NULL);
	//m_btnAgo.SizeToContent();
	m_btnNext.LoadBitmaps(IDB_BITMAP_NEXT, NULL, NULL, NULL);
	//m_btnNext.SizeToContent();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CHelpDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetWindowRect(&rect);
	
	pDC->FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(0, 0, 0));

	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CHelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_bFirst == false) {
		SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
		for (int i = 0; i < 200; i++) {
			SetLayeredWindowAttributes(0, i, LWA_ALPHA);
			Sleep(3);
		}
		m_bFirst = true;
	}
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CRect superRect;
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	BITMAP info;
	switch (m_nStage) {
	case 0: {
		CBitmap help_tabcontrol, help_graph;
		CBitmap* oldhelp_tabcontrol = NULL, * oldhelp_graph = NULL;

		pMain->GetDlgItem(IDC_TAB_SELECTION)->GetWindowRect(&superRect);
		pMain->ScreenToClient(superRect);
		help_tabcontrol.LoadBitmapW(IDB_BITMAP_HELP_HELPING1);
		oldhelp_tabcontrol = MemDC.SelectObject(&help_tabcontrol);
		help_tabcontrol.GetBitmap(&info);
		dc.StretchBlt(superRect.left, superRect.top + 30, superRect.Width(), superRect.Height(),
			&MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
		MemDC.SelectObject(oldhelp_tabcontrol);

		pMain->GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&superRect);
		pMain->ScreenToClient(superRect);
		help_graph.LoadBitmapW(IDB_BITMAP_HELP_HELPING2);
		oldhelp_graph = MemDC.SelectObject(&help_graph);
		help_graph.GetBitmap(&info);
		dc.StretchBlt(superRect.left, superRect.top + 30, superRect.Width(), superRect.Height(),
			&MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
		MemDC.SelectObject(oldhelp_graph);
		help_tabcontrol.DeleteObject();
		help_graph.DeleteObject();
		MemDC.DeleteDC();
	}
		break;
	case 1: {
		CBitmap help, * oldhelp;
		pMain->GetWindowRect(&superRect);
		pMain->ScreenToClient(superRect);
		help.LoadBitmapW(IDB_BITMAP_HELP_HELPING3);
		oldhelp = MemDC.SelectObject(&help);
		help.GetBitmap(&info);
		dc.StretchBlt(0, 0, superRect.Width(), superRect.Height(),
			&MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
		MemDC.SelectObject(oldhelp);
	}
		break;
	case 2: {
		CBitmap help, * oldhelp;
		pMain->GetWindowRect(&superRect);
		pMain->ScreenToClient(superRect);
		help.LoadBitmapW(IDB_BITMAP_HELP_HELPING4);
		oldhelp = MemDC.SelectObject(&help);
		help.GetBitmap(&info);
		dc.StretchBlt(0, 0, superRect.Width(), superRect.Height(),
			&MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
		MemDC.SelectObject(oldhelp);
	}
		break;
	case 3: {
		CBitmap help, * oldhelp;
		pMain->GetWindowRect(&superRect);
		pMain->ScreenToClient(superRect);
		help.LoadBitmapW(IDB_BITMAP_HELP_HELPING5);
		oldhelp = MemDC.SelectObject(&help);
		help.GetBitmap(&info);
		dc.StretchBlt(0, 0, superRect.Width(), superRect.Height(),
			&MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
		MemDC.SelectObject(oldhelp);
	}
		break;
	case 4:
		break;
	case 5:
		break;
	}
}


void CHelpDlg::OnBnClickedButtonNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_nStage)
	{
	case 0:
		m_nStage++;
		Invalidate();
		break;
	case 1:
		m_nStage++;
		Invalidate();
		break;
	case 2:
		m_btnNext.MoveWindow(m_rectNext.left, m_rectNext.top - (3 * m_rectNext.Height()), m_rectNext.Width(), m_rectNext.Height());
		m_nStage++;
		Invalidate();
		break;
	case 3:
		m_nStage++;
		Invalidate();
		SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
		for (int i = 200; i > 0; i--) {
			SetLayeredWindowAttributes(0, i, LWA_ALPHA);
			Sleep(3);
		}
		CHelpDlg::OnOK();
		break;
	case 4:
		m_nStage++;
		break;
	case 5:
		SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
		for (int i = 200; i > 0; i--) {
			SetLayeredWindowAttributes(0, i, LWA_ALPHA);
			Sleep(3);
		}
		CHelpDlg::OnOK();
		m_nStage++;
		break;

	}

}


void CHelpDlg::OnBnClickedButtonAgo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_nStage)
	{
	case 0:
		break;
	case 1:
		m_nStage--;
		Invalidate();
		break;
	case 2:
		m_nStage--;
		Invalidate();
		break;
	case 3:
		m_btnNext.MoveWindow(m_rectNext.left, m_rectNext.top, m_rectNext.Width(), m_rectNext.Height());
		m_nStage--;
		Invalidate();
		break;
	case 4:
		m_nStage--;
		Invalidate();
		break;
	case 5:
		m_nStage--;
		break;
	}
}
