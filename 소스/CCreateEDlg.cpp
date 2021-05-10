// CCreateEDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CCreateEDlg.h"
#include "afxdialogex.h"
#include "Function_1Dlg.h"


// CCreateEDlg 대화 상자

IMPLEMENT_DYNAMIC(CCreateEDlg, CDialogEx)

CCreateEDlg::CCreateEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE_E, pParent)
	, m_nX(0)
	, m_nY(0)
	, m_nB(0)
	, m_nA(0)
{

}

CCreateEDlg::~CCreateEDlg()
{
}

void CCreateEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	DDX_Text(pDX, IDC_EDIT_B, m_nB);
	DDX_Text(pDX, IDC_EDIT_A, m_nA);
}


BEGIN_MESSAGE_MAP(CCreateEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CCreateEDlg::OnBnClickedButtonOk)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCreateEDlg 메시지 처리기


BOOL CCreateEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CFont font;
	LOGFONT logfont;

	GetDlgItem(IDC_EDIT_X)->GetFont()->GetLogFont(&logfont);
	
	logfont.lfWeight = 100;
	logfont.lfHeight = 40;
	
	font.CreateFontIndirectW(&logfont);

	GetDlgItem(IDC_EDIT_X)->SetFont(&font);
	GetDlgItem(IDC_EDIT_Y)->SetFont(&font);
	GetDlgItem(IDC_EDIT_A)->SetFont(&font);
	GetDlgItem(IDC_EDIT_B)->SetFont(&font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCreateEDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CDC tmp;
	CRect rect;
	CBitmap bmp;
	BITMAP info;

	CRect r;
	GetDlgItem(IDC_BUTTON_OK)->GetWindowRect(&r);
	ScreenToClient(&r);

	GetWindowRect(&rect);
	ScreenToClient(&rect);
	bmp.LoadBitmapW(IDB_BITMAP_CREATE_E);
	bmp.GetBitmap(&info);
	tmp.CreateCompatibleDC(&dc);
	tmp.SelectObject(&bmp);
	//dc.BitBlt(0, 0, rect.Width(), rect.Height(), &tmp, 0, 0, SRCCOPY);
	dc.StretchBlt(0, 0, info.bmWidth , info.bmHeight, &tmp, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
	bmp.DeleteObject();
}

void CCreateEDlg::OnBnClickedButtonOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString m_strFunction_E = NULL;
	CString strX, strY, strA, strB;
	strX.Format(_T("%.2lf"), m_nX);
	strY.Format(_T("%.2lf"), m_nY);
	strA.Format(_T("%.2lf"), m_nA * m_nA);
	strB.Format(_T("%.2lf"), m_nB * m_nB);
	m_strFunction_E = _T("(x-") + strX + _T(")^2/") + strA + _T("+(y-") + strY + _T(")^2/") + strB;
	MessageBox(m_strFunction_E);

	CFunction1Dlg* pMain;
	pMain = (CFunction1Dlg*)AfxGetMainWnd();

	pMain->m_dlgFunctionEx.m_strFunction = m_strFunction_E;
	pMain->m_dlgFunctionEx.UpdateData(FALSE);
	CDialogEx::OnOK();
	CCreateEDlg::OnOK();
}


BOOL CCreateEDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CRect rect, r;
	//GetWindowRect(&rect);
	//GetWindowRect(&r);
	//CBitmap title, * oldtitle;
	//CDC MemDC;
	//BITMAP info;

	//MemDC.CreateCompatibleDC(pDC);
	//title.LoadBitmapW(IDB_BITMAP_CREATE_E);
	//title.GetBitmap(&info);
	//oldtitle = MemDC.SelectObject(&title);
	////pDC->BitBlt(0, 0, info.bmWidth, info.bmHeight, &MemDC, 0, 0, SRCCOPY);
	//pDC->StretchBlt(0, 0, rect.Width() - r.Width(), rect.Height(), &MemDC, 0, 0, info.bmWidth, info.bmHeight, SRCCOPY);
	//MemDC.SelectObject(oldtitle);
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}
