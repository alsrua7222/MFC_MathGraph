// CCreateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CCreateDlg.h"
#include "afxdialogex.h"
#include "Function_1Dlg.h"


// CCreateDlg 대화 상자

IMPLEMENT_DYNAMIC(CCreateDlg, CDialogEx)

CCreateDlg::CCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CREATE, pParent)
	, m_nX0(0)
	, m_nX1(0)
	, m_nX2(0)
	, m_nX3(0)
	, m_nX4(0)
	, m_nX5(0)
	, m_nX6(0)
	, m_nX7(0)
	, m_nX8(0)
	, m_nX9(0)
	, m_checkX0(FALSE)
	, m_checkX1(FALSE)
	, m_checkX2(FALSE)
	, m_checkX3(FALSE)
	, m_checkX4(FALSE)
	, m_checkX5(FALSE)
	, m_checkX6(FALSE)
	, m_checkX7(FALSE)
	, m_checkX8(FALSE)
	, m_checkX9(FALSE)
	, m_comboX1(_T(""))
	, m_comboX2(_T(""))
	, m_comboX3(_T(""))
	, m_comboX4(_T(""))
	, m_comboX5(_T(""))
	, m_comboX6(_T(""))
	, m_comboX7(_T(""))
	, m_comboX8(_T(""))
	, m_comboX9(_T(""))
{

}

CCreateDlg::~CCreateDlg()
{
}

void CCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X0, m_nX0);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_X3, m_nX3);
	DDX_Text(pDX, IDC_EDIT_X4, m_nX4);
	DDX_Text(pDX, IDC_EDIT_X5, m_nX5);
	DDX_Text(pDX, IDC_EDIT_X6, m_nX6);
	DDX_Text(pDX, IDC_EDIT_X7, m_nX7);
	DDX_Text(pDX, IDC_EDIT_X8, m_nX8);
	DDX_Text(pDX, IDC_EDIT_X9, m_nX9);

	DDX_Check(pDX, IDC_CHECK_X0, m_checkX0);
	DDX_Check(pDX, IDC_CHECK_X1, m_checkX1);
	DDX_Check(pDX, IDC_CHECK_X2, m_checkX2);
	DDX_Check(pDX, IDC_CHECK_X3, m_checkX3);
	DDX_Check(pDX, IDC_CHECK_X4, m_checkX4);
	DDX_Check(pDX, IDC_CHECK_X5, m_checkX5);
	DDX_Check(pDX, IDC_CHECK_X6, m_checkX6);
	DDX_Check(pDX, IDC_CHECK_X7, m_checkX7);
	DDX_Check(pDX, IDC_CHECK_X8, m_checkX8);
	DDX_Check(pDX, IDC_CHECK_X9, m_checkX9);
	//  DDX_CBString(pDX, IDC_COMBO_X0, m_comboX0);
	DDX_CBString(pDX, IDC_COMBO_X1, m_comboX1);
	DDX_CBString(pDX, IDC_COMBO_X2, m_comboX2);
	DDX_CBString(pDX, IDC_COMBO_X3, m_comboX3);
	DDX_CBString(pDX, IDC_COMBO_X4, m_comboX4);
	DDX_CBString(pDX, IDC_COMBO_X5, m_comboX5);
	DDX_CBString(pDX, IDC_COMBO_X6, m_comboX6);
	DDX_CBString(pDX, IDC_COMBO_X7, m_comboX7);
	DDX_CBString(pDX, IDC_COMBO_X8, m_comboX8);
	DDX_CBString(pDX, IDC_COMBO_X9, m_comboX9);
}


BEGIN_MESSAGE_MAP(CCreateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_X0, &CCreateDlg::OnClickedCheckX0)
	ON_BN_CLICKED(IDC_CHECK_X1, &CCreateDlg::OnClickedCheckX1)
	ON_BN_CLICKED(IDC_CHECK_X2, &CCreateDlg::OnClickedCheckX2)
	ON_BN_CLICKED(IDC_CHECK_X3, &CCreateDlg::OnClickedCheckX3)
	ON_BN_CLICKED(IDC_CHECK_X4, &CCreateDlg::OnClickedCheckX4)
	ON_BN_CLICKED(IDC_CHECK_X5, &CCreateDlg::OnClickedCheckX5)
	ON_BN_CLICKED(IDC_CHECK_X6, &CCreateDlg::OnClickedCheckX6)
	ON_BN_CLICKED(IDC_CHECK_X7, &CCreateDlg::OnClickedCheckX7)
	ON_BN_CLICKED(IDC_CHECK_X8, &CCreateDlg::OnClickedCheckX8)
	ON_BN_CLICKED(IDC_CHECK_X9, &CCreateDlg::OnClickedCheckX9)
	ON_BN_CLICKED(IDOK, &CCreateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateDlg 메시지 처리기


BOOL CCreateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	((CComboBox*)GetDlgItem(IDC_COMBO_X1))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X2))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X3))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X4))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X5))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X6))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X7))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X8))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_X9))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CCreateDlg::OnClickedCheckX0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX0 == TRUE) {
		GetDlgItem(IDC_EDIT_X0)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X0)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX1 == TRUE) {
		GetDlgItem(IDC_EDIT_X1)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X1)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX2 == TRUE) {
		GetDlgItem(IDC_EDIT_X2)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X2)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX3 == TRUE) {
		GetDlgItem(IDC_EDIT_X3)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X3)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX4 == TRUE) {
		GetDlgItem(IDC_EDIT_X4)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X4)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX5 == TRUE) {
		GetDlgItem(IDC_EDIT_X5)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X5)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX6 == TRUE) {
		GetDlgItem(IDC_EDIT_X6)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X6)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX7 == TRUE) {
		GetDlgItem(IDC_EDIT_X7)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X7)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX8 == TRUE) {
		GetDlgItem(IDC_EDIT_X8)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X8)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnClickedCheckX9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (m_checkX9 == TRUE) {
		GetDlgItem(IDC_EDIT_X9)->SendMessage(EM_SETREADONLY, 0, 0);
	}
	else {
		GetDlgItem(IDC_EDIT_X9)->SendMessage(EM_SETREADONLY, 1, 0);
	}
}


void CCreateDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	m_strFunction.Empty();
	if (m_checkX9) {
		CString m_strN;
		m_strN.Format(_T("%d"), m_nX9);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^9"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX8) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX8);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^8"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX7) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX7);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^7"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX6) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX6);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^6"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX5) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX5);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^5"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX4) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX4);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^4"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX3) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX3);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^3"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX2) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX2);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^2"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX1) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX1);
		m_strFunction = m_strFunction + m_strN;
		m_strN.Format(_T("x^1"));
		m_strFunction = m_strFunction + m_strN;
	}
	if (m_checkX0) {
		CString m_strN;
		if (m_strFunction != "") {
			m_strN.Format(_T("+"));
			m_strFunction = m_strFunction + m_strN;
		}

		m_strN.Format(_T("%d"), m_nX0);
		m_strFunction = m_strFunction + m_strN;
	}

	MessageBox(m_strFunction);

	CFunction1Dlg* pMain;
	pMain = (CFunction1Dlg*)AfxGetMainWnd();

	pMain->m_dlgFunctionEx.m_strFunction = m_strFunction;
	pMain->m_dlgFunctionEx.UpdateData(FALSE);
	CDialogEx::OnOK();
}
