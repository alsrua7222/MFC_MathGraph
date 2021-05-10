
// Function_1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Function_1.h"
#include "Function_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CSketch.h"
#include "CTest.h"
#include "CFunctionProc.h"
#include "CTitleDlg.h"
#include "DataBase.h"


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFunction1Dlg 대화 상자



CFunction1Dlg::CFunction1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FUNCTION_1_DIALOG, pParent)
	, m_strX(_T(""))
	, m_strY(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFunction1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SELECTION, m_tabSelection);
	DDX_Control(pDX, IDC_STATIC_VIEW, m_staticView);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btnReset);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_btnHelp);
	DDX_Control(pDX, IDC_BUTTON_HIDESHOW, m_btnHideShow);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_btnLoad);
	DDX_Text(pDX, IDC_EDIT1, m_strX);
	DDX_Text(pDX, IDC_EDIT2, m_strY);
	DDX_Control(pDX, IDC_STATIC_X, m_staticX);
	DDX_Control(pDX, IDC_STATIC_Y, m_staticY);
}

BEGIN_MESSAGE_MAP(CFunction1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SELECTION, &CFunction1Dlg::OnSelchangeTabSelection)
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
//	ON_WM_RBUTTONDBLCLK()
//	ON_WM_GETMINMAXINFO()
//	ON_WM_NCPAINT()
ON_BN_CLICKED(IDC_BUTTON_HELP, &CFunction1Dlg::OnClickedButtonHelp)
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFunction1Dlg::OnBnClickedButtonSave)
ON_BN_CLICKED(IDC_BUTTON_LOAD, &CFunction1Dlg::OnBnClickedButtonLoad)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CFunction1Dlg::OnBnClickedButtonReset)
ON_BN_CLICKED(IDC_BUTTON_HIDESHOW, &CFunction1Dlg::OnBnClickedButtonHideshow)
END_MESSAGE_MAP()


// CFunction1Dlg 메시지 처리기

BOOL CFunction1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	{//Dialog 세부사항
		m_btnReset.LoadBitmaps(IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP3, IDB_BITMAP4);
		//m_btnReset.SizeToContent();
		m_btnHelp.LoadBitmaps(IDB_BITMAP_HELP_1, IDB_BITMAP_HELP_2, IDB_BITMAP_HELP_3, IDB_BITMAP_HELP_4);
		//m_btnHelp.SizeToContent();
		m_btnLoad.LoadBitmaps(IDB_BITMAP_Load_1, IDB_BITMAP_Load_2, IDB_BITMAP_Load_3, IDB_BITMAP_Load_4);
		//m_btnLoad.SizeToContent();
		m_btnSave.LoadBitmaps(IDB_BITMAP_Save_1, IDB_BITMAP_Save_2, IDB_BITMAP_Save_3, IDB_BITMAP_Save_4);
		//m_btnSave.SizeToContent();
		m_btnHideShow.LoadBitmaps(IDB_BITMAP_HIDESHOW_1, IDB_BITMAP_HIDESHOW_2, IDB_BITMAP_HIDESHOW_3, IDB_BITMAP_HIDESHOW_4);
		//m_btnHideShow.SizeToContent();

		//HBITMAP hBmp1, hBmp2;
		//hBmp1 = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_X), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
		//hBmp2 = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_Y), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
		//((CStatic*)GetDlgItem(IDC_STATIC_X))->SetBitmap(hBmp1);
		//((CStatic*)GetDlgItem(IDC_STATIC_Y))->SetBitmap(hBmp2);

		CFont font;
		LOGFONT logfont;
		GetDlgItem(IDC_EDIT1)->GetFont()->GetLogFont(&logfont);
		logfont.lfWeight = 100;
		logfont.lfHeight = 40;
		font.CreateFontIndirectW(&logfont);
		GetDlgItem(IDC_EDIT1)->SetFont(&font);
		GetDlgItem(IDC_EDIT2)->SetFont(&font);
	}
	{//Color 색깔 지정
		m_color[0] = RGB(218, 63, 58);//빨
		m_color[1] = RGB(255, 0, 255);//분
		m_color[2] = RGB(243, 117, 58);//주
		m_color[3] = RGB(255, 223, 62);//노
		m_color[4] = RGB(0, 118, 68);//초
		m_color[5] = RGB(1, 120, 124);//청
		m_color[6] = RGB(56, 113, 166);//파
		m_color[7] = RGB(42, 54, 92);//남
		m_color[8] = RGB(118, 78, 130);//보
		m_color[9] = RGB(136, 86, 63);//갈
	}
	{//변수 초기화
		s =	new CSketch(IDC_STATIC_VIEW);
		m_nSizeWheel = 25;
		for (int i = 0; i < INDEX; i++) {
			m_info_L.degree[i] = false;
			m_info_L.expo[i] = 0;
			m_info_L.coef[i] = 0;
			m_nVaildSelected[i] = VAILD_NOPE;
			m_bOnoff[i] = false;
		}
		m_info_E.a = 0;
		m_info_E.b = 0;
		m_info_E.x = 0;
		m_info_E.y = 0;
	}
	{//tabControl 세부사항
		m_tabSelection.DeleteAllItems();
		m_tabSelection.InsertItem(0, _T("함수식"));
		m_tabSelection.InsertItem(1, _T("스케치"));

		CRect rect;
		m_dlgFunctionEx.Create(IDD_DIALOG_FUNCTION, &m_tabSelection);
		m_dlgFunctionEx.GetWindowRect(&rect);
		m_dlgFunctionEx.MoveWindow(5, 25, rect.Width(), rect.Height());
		m_dlgFunctionEx.ShowWindow(SW_SHOW);

		m_dlgSketch.Create(IDD_DIALOG_SKETCH, &m_tabSelection);
		m_dlgSketch.GetWindowRect(&rect);
		m_dlgSketch.MoveWindow(5, 25, rect.Width(), rect.Height());
		m_dlgSketch.ShowWindow(SW_HIDE);
	}
	/*
	CString tmp = _T("(x-3)^2/25+(y+1)^2/16");
	CFunctionProc proc;
	proc.StrToData_E(tmp, &m_info_E);
	CString str;
	str.Format(_T("x:%lf, y:%lf, a:%lf, b:%lf"), m_info_E.x, m_info_E.y, m_info_E.a, m_info_E.b);
	MessageBox(str);
	*/
	{//업데이트
		UpdateData(FALSE);

	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFunction1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFunction1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// TODO: 여기에 구현 코드 추가.
		CClientDC dc(this);
		CRect rectX, rectY;
		CImage bmpX, bmpY;
		m_staticX.GetWindowRect(&rectX);
		ScreenToClient(rectX);
		m_staticY.GetWindowRect(&rectY);
		ScreenToClient(rectY);
		bmpX.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_X);
		bmpY.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP_Y);
		dc.SetStretchBltMode(COLORONCOLOR);
		bmpX.Draw(dc, rectX);
		bmpY.Draw(dc, rectY);
		CDialogEx::OnPaint();
	}
	// TODO: 여기에 구현 코드 추가.
	
	//처음에 나타나는 레이아웃.
	if (!m_bFirst) {
		s->Draw_Layout(&m_nSizeWheel);
		m_bFirst = true;
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFunction1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CFunction1Dlg::OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelection = m_tabSelection.GetCurSel();

	switch (nSelection){
	case 0:
		m_dlgFunctionEx.ShowWindow(SW_SHOW);
		m_dlgSketch.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_dlgFunctionEx.ShowWindow(SW_HIDE);
		m_dlgSketch.ShowWindow(SW_SHOW);
		break;
		}

	*pResult = 0;
}


void CFunction1Dlg::UpdateDrawing()
{
	// TODO: 여기에 구현 코드 추가.

	CRect rectView;
	GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&rectView);
	ScreenToClient(&rectView);
	rectView.DeflateRect(1, 1, 1, 1);
	
	InvalidateRect(&rectView);
}


void CFunction1Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CFunction1Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_CONTROL) {//컨트룰 누른 상태 (Ctrl + mousewheel)
		if (zDelta > 0) m_nSizeWheel++;
		else if(zDelta<0)m_nSizeWheel--;
		//
		CString str;
		CFunctionProc fp;
		s->Draw_Layout(&m_nSizeWheel);
		//str = _T("2x^2");
		//fp.StrToData_L(str, &m_info_L);
		////t.toString_MSG(&m_info); //정상적으로 데이터 기입하였는지 확인 용도.
		//s->Draw_Line(m_info_L);
		//m_info_E.x = 3;
		//m_info_E.y = -1;
		//m_info_E.a = 4;
		//m_info_E.b = 1;
		//s->Draw_Ellipse(m_info_E);

		for (int i = 0; i < INDEX; i++) {
			if (m_nVaildSelected[i] == VAILD_LINE && m_bOnoff[i] == true) {//Line
				str = m_dlgFunctionEx.m_listFunction.GetItemText(i, 1);
				fp.StrToData_L(str, &m_info_L);
				s->Draw_Line(m_info_L, m_color[i]);
			}
			else if (m_nVaildSelected[i] == VAILD_ELLIPSE && m_bOnoff[i] == true) {//Ellipse
				str = m_dlgFunctionEx.m_listFunction.GetItemText(i, 1);
				fp.StrToData_E(str, &m_info_E);
				s->Draw_Ellipse(m_info_E, m_color[i]);
			}
			else {//None

			}
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CFunction1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_dlgSketch.m_bDrawing) {
		//s->Sketch_Line(&m_info_L, 1, &m_bLBDown, point);
		int count = m_dlgSketch.m_listFunction1.GetItemCount();
		if (!m_dlgSketch.m_bLE){
			s->Sketch_Line(&m_info_L, 1, &m_bLBDown, point, m_color[count]);
		}
		else {
			s->Sketch_Ellipse(&m_info_E, 1, &m_bLBDown, point, m_color[count]);
		}
		CString x, y;
		s->Sketch_CursurPos(true, x, y, point);
		m_strX = x;
		m_strY = y;
		UpdateData(FALSE);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CFunction1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_dlgSketch.m_bDrawing) {
		//s->Sketch_Line(&m_info_L, 2, &m_bLBDown, point);
		int count = m_dlgSketch.m_listFunction1.GetItemCount();
		if (count >= 10) return;
		if (!m_dlgSketch.m_bLE) {
			s->Sketch_Line(&m_info_L, 2, &m_bLBDown, point, m_color[count]);
		}
		else{

			s->Sketch_Ellipse(&m_info_E, 2, &m_bLBDown, point, m_color[count]);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}




//void CFunction1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	if (m_bRBDown) {
//		//s->Sketch_Line(&m_info_L, 3, &m_bLBDown, point);
//		s->Sketch_Ellipse(&m_info_E, 3, &m_bLBDown, point);
//	}
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


//void CFunction1Dlg::OnRButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	if (!m_bLBDown) {
//		m_bRBDown = !m_bRBDown;
//	}
//	CDialogEx::OnRButtonDblClk(nFlags, point);
//}


//void CFunction1Dlg::OnBnClickedButtonAllonoff()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
//
//
//}


//void CFunction1Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	
//	CDialogEx::OnGetMinMaxInfo(lpMMI);
//}


//void CFunction1Dlg::OnNcPaint()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	// 그리기 메시지에 대해서는 CDialogEx::OnNcPaint()을(를) 호출하지 마십시오.
//	
//}


void CFunction1Dlg::OnClickedButtonHelp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CHelpDlg m_dlgHelp;

	m_dlgHelp.DoModal();

	m_dlgHelp.DestroyWindow();
}


BOOL CFunction1Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetWindowRect(&rect);
	pDC->FillSolidRect(0, 0, rect.Width(), rect.Height(), BKGND);

	return TRUE;
}


void CFunction1Dlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString tmp = _T("");
	CString str;
	for (int i = 0; i < INDEX; i++) {
		if (m_nVaildSelected[i] == VAILD_LINE) {//Line
			tmp = m_dlgFunctionEx.m_listFunction.GetItemText(i, 1);
			str += _T("LINE\t") + tmp + _T("\n");
		}
		else if (m_nVaildSelected[i] == VAILD_ELLIPSE) {//Ellipse
			tmp = m_dlgFunctionEx.m_listFunction.GetItemText(i, 1);
			str += _T("ELLIPSE\t") + tmp + _T("\n");
		}
		else {//None

		}
	}
	DataBase db;
	db.DBSave_txt(str);
}


void CFunction1Dlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DataBase db;
	CString str;
	db.DBLoad_txt(str);
	CString tmp;

	int count = 0;
	for (int i = 0; i < str.GetLength(); i++) {
		if (str[i] == '\t') {
			if (tmp == _T("LINE")) {
				m_nVaildSelected[count] = VAILD_LINE;
				tmp.Empty();
			}
			else if(tmp == _T("ELLIPSE")){
				m_nVaildSelected[count] = VAILD_ELLIPSE;
				tmp.Empty();
			}
			else {
				MessageBox(_T("Load Error: Not found Code(1001)"));
				break;
			}
		}
		else if (str[i] == '\n') {
			m_dlgFunctionEx.m_strFunction = tmp;
			m_dlgFunctionEx.UpdateData(FALSE);
			m_dlgFunctionEx.OnClickedButtonAdd();
			count++;
			if (count >= 10) {
				MessageBox(_T("Load Error: Too much Count(1002)"));
				break;
			}
			tmp.Empty();
		}
		else {
			tmp += str[i];
		}
	}
}


void CFunction1Dlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dlgFunctionEx.m_listFunction.DeleteAllItems();
	m_dlgSketch.m_listFunction1.DeleteAllItems();
	for (int i = 0; i < INDEX; i++) {
		m_nVaildSelected[i] = VAILD_NOPE;
		m_bOnoff[i] = false;
	}
	m_bFirst = !m_bFirst;
	UpdateData(FALSE);
	OnMouseWheel(MK_CONTROL, 0, NULL);
}


void CFunction1Dlg::OnBnClickedButtonHideshow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bFirst2) {
		for (int i = 0; i < INDEX; i++) {
			if (m_nVaildSelected[i] != VAILD_NOPE) {
				m_bOnoff[i] = true;
				m_dlgFunctionEx.m_listFunction.SetItemText(i, 2, _T("보이기"));
				m_dlgSketch.m_listFunction1.SetItemText(i, 2, _T("보이기"));
				m_dlgFunctionEx.UpdateData(FALSE);
				m_dlgSketch.UpdateData(FALSE);
			}
		}
	}
	else {
		for (int i = 0; i < INDEX; i++) {
			if (m_nVaildSelected[i] != VAILD_NOPE) {
				m_bOnoff[i] = false;
				m_dlgFunctionEx.m_listFunction.SetItemText(i, 2, _T("감추기"));
				m_dlgSketch.m_listFunction1.SetItemText(i, 2, _T("감추기"));
				m_dlgFunctionEx.UpdateData(FALSE);
				m_dlgSketch.UpdateData(FALSE);
			}
		}
	}
	OnMouseWheel(MK_CONTROL, 0, NULL);
	m_bFirst2 = !m_bFirst2;
}
