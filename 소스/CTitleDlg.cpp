// CTitleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CTitleDlg.h"
#include "afxdialogex.h"
#include "Function_1Dlg.h"


// CTitleDlg 대화 상자

IMPLEMENT_DYNAMIC(CTitleDlg, CDialogEx)

CTitleDlg::CTitleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TITLE, pParent)
{

}

CTitleDlg::~CTitleDlg()
{
}

void CTitleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTitleDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
//	ON_BN_CLICKED(IDOK, &CTitleDlg::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTitleDlg 메시지 처리기


BOOL CTitleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CTitleDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetWindowRect(&rect);
	
	CBitmap title, *oldtitle;
	CDC MemDC;
	BITMAP info;
	
	MemDC.CreateCompatibleDC(pDC);
	title.LoadBitmapW(IDB_BITMAP_TITLE);
	title.GetBitmap(&info);
	oldtitle = MemDC.SelectObject(&title);
	//pDC->BitBlt(0, 0, info.bmWidth, info.bmHeight, &MemDC, 0, 0, SRCCOPY);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
	MemDC.SelectObject(oldtitle);

	SetTimer(1, 2000, NULL);
	m_bFirst = false;
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CTitleDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CreateShow();
	//OnBnClickedOk();
}


//void CTitleDlg::OnBnClickedOk()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	
//	CDialogEx::OnOK();
//}


void CTitleDlg::Destroy()
{
	// TODO: 여기에 구현 코드 추가.
	CTitleDlg::OnOK();
}


void CTitleDlg::CreateShow()
{
	// TODO: 여기에 구현 코드 추가.
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	if (!m_bFirst){
		for (int i = 0; i < 255; i++) {
			SetLayeredWindowAttributes(0, i, LWA_ALPHA);
			Sleep(3);
		}
	}
	else{
		for (int i = 255; i > 0; i--) {
			SetLayeredWindowAttributes(0, i, LWA_ALPHA);
			Sleep(3);
		}
	}
}


void CTitleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	KillTimer(1);
	m_bFirst = true;
	OnPaint();
	CDialogEx::OnOK();
	CDialogEx::OnTimer(nIDEvent);
}
