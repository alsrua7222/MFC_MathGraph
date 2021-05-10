// CFunctionExDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CFunctionExDlg.h"
#include "afxdialogex.h"
#include "CTest.h"
#include "CSketchDlg.h"
#include "CCreateDlg.h"
#include "CCreateEDlg.h"

// CFunctionExDlg 대화 상자

IMPLEMENT_DYNAMIC(CFunctionExDlg, CDialogEx)

CFunctionExDlg::CFunctionExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FUNCTION, pParent)
	, m_strFunction(_T(""))
{
	m_bLE = false;
	m_nSelectedItem = 0;
	

}

CFunctionExDlg::~CFunctionExDlg()
{
}

void CFunctionExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNCTION, m_strFunction);
	DDX_Control(pDX, IDC_LIST_FUNCTION, m_listFunction);
}


BEGIN_MESSAGE_MAP(CFunctionExDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CFunctionExDlg::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CFunctionExDlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CFunctionExDlg::OnClickedButtonModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FUNCTION, &CFunctionExDlg::OnItemchangedListFunction)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CFunctionExDlg::OnBnClickedButtonOpen)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_FUNCTION, &CFunctionExDlg::OnClickListFunction)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_FUNCTION, &CFunctionExDlg::OnCustomdrawListFunction)
	ON_COMMAND(IDC_RADIO_LINE, &CFunctionExDlg::OnRadioLine)
	ON_COMMAND(IDC_RADIO_ELLIPSE, &CFunctionExDlg::OnRadioEllipse)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_ONOFF, &CFunctionExDlg::OnClickedButtonOnoff)
END_MESSAGE_MAP()


// CFunctionExDlg 메시지 처리기



BOOL CFunctionExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	CRect rect;
	GetDlgItem(IDC_LIST_FUNCTION)->GetClientRect(&rect);
	int W = rect.Width();
	//퍼센트 비율임.
	//W* 와 / 100.0 사이에 있는 숫자만 조정하도록 하세요.
	int w[3];
	w[0] = (int)W * 15 / 100.0;
	w[1] = (int)W * 60 / 100.0;
	w[2] = W - w[0] - w[1];
	LPWSTR list[3] = { _T("번호"),_T("함수식"),_T("보이기/감추기")};
	int nWidth[3] = { w[0], w[1], w[2] };

	for (int i = 0; i < 3; i++) {
		m_listFunction.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}

	m_listFunction.SetExtendedStyle(m_listFunction.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//m_listFunction.SetTextColor(RGB(255, 255, 255));
	m_bLE = false;
	((CButton*)GetDlgItem(IDC_RADIO_LINE))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

	CFont font;
	LOGFONT logfont;

	::ZeroMemory(&logfont, sizeof(logfont));
	logfont.lfWeight = 100;
	logfont.lfHeight = 30;
	
	::lstrcpy(logfont.lfFaceName, (LPCWSTR)"맑은 고딕");
	font.CreateFontIndirectW(&logfont);

	GetDlgItem(IDC_STATIC_TEXT_FUNCTION)->SetFont(&font);
	font.Detach();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CFunctionExDlg::OnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int m_nCount = m_listFunction.GetItemCount();
	
	//요소가 10개밖에 지원못함. 그러므로 삭제.
	if (m_nCount >= 10) return;
	CFunction1Dlg* pMain;
	pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CString strCount;
	CTest test;
	UpdateData(TRUE);

	if (!m_bLE) {//직선
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
		}
		else{// if (1000 == test.TestText(m_strFunction)) {
			strCount.Format(_T("%d"),m_nCount+1);
			m_listFunction.InsertItem(m_nCount, strCount);
			m_listFunction.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			m_listFunction.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			//m_listFunction.SetTextBkColor(pMain->m_color[m_nCount]);
			pMain->m_dlgSketch.m_listFunction1.InsertItem(m_nCount, strCount);
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);

			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

			m_strFunction.Empty();
			pMain->m_bOnoff[m_nCount] = true;
			pMain->m_nVaildSelected[m_nCount] = VAILD_LINE;
			UpdateData(FALSE);
			pMain->OnMouseWheel(MK_CONTROL, NULL, NULL);
			pMain->UpdateData(FALSE);
		}
		//else if(1000!=test.TestText(m_strFunction)){
		//	AfxMessageBox(_T("함수가 아님"));
		//}
		return;
	}
	else {//원
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
		}
		else {// if (1000 == test.TestText(m_strFunction)) {
			strCount.Format(_T("%d"), m_nCount + 1);
			m_listFunction.InsertItem(m_nCount, strCount);
			m_listFunction.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			m_listFunction.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			//m_listFunction.SetTextBkColor(pMain->m_color[m_nCount]);
			pMain->m_dlgSketch.m_listFunction1.InsertItem(m_nCount, strCount);
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

			m_strFunction.Empty();
			pMain->m_bOnoff[m_nCount] = true;
			pMain->m_nVaildSelected[m_nCount] = VAILD_ELLIPSE;
			UpdateData(FALSE);
			pMain->OnMouseWheel(MK_CONTROL, NULL, NULL);
			pMain->UpdateData(FALSE);
		}
		//else if(1000!=test.TestText(m_strFunction)){
		//	AfxMessageBox(_T("함수가 아님"));
		//}
		return;
	}
}


void CFunctionExDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0) {
		CFunction1Dlg* pMain;
		pMain = (CFunction1Dlg*)AfxGetMainWnd();
		int count = m_listFunction.GetItemCount();
		m_listFunction.DeleteItem(m_nSelectedItem);

		for (int i = m_nSelectedItem - 1; i < m_listFunction.GetItemCount(); i++) {
			if (i == 9) {
				break;
			}
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_listFunction.SetItemText(i, 0, strIndex);
			pMain->m_nVaildSelected[i] = pMain->m_nVaildSelected[i + 1];
			pMain->m_bOnoff[i] = pMain->m_bOnoff[i + 1];
		}
		pMain->m_nVaildSelected[count - 1] = VAILD_NOPE;
		pMain->m_bOnoff[count - 1] = false;
		m_strFunction.Empty();


		pMain->m_dlgSketch.m_listFunction1.DeleteItem(m_nSelectedItem);
		pMain->m_dlgSketch.UpdateData(FALSE);

		for (int i = m_nSelectedItem - 1; i < pMain->m_dlgSketch.m_listFunction1.GetItemCount(); i++) {
			if (i == 9) {
				break;
			}
			CString strIndex;

			strIndex.Format(_T("%d"), i+1);
			pMain->m_dlgSketch.m_listFunction1.SetItemText(i, 0, strIndex);
		}

		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		pMain->OnMouseWheel(MK_CONTROL, 0, NULL);
	}
	else {
		AfxMessageBox(_T("아이템을 선택하지 않았습니다."));
	}
}


void CFunctionExDlg::OnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString strFunction, strIndex;
	strFunction = m_strFunction;
	CTest test;

	if (!m_bLE) {//직선
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
			return;
		}
		else {
			// if (1000 == test.TestText(m_strFunction)) {
			strIndex.Format(_T("%d"), m_nSelectedItem + 1);
			m_listFunction.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			CFunction1Dlg* pMain;
			pMain = (CFunction1Dlg*)AfxGetMainWnd();
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

			m_strFunction.Empty();

			pMain->m_nVaildSelected[m_nSelectedItem] = VAILD_LINE;

			pMain->UpdateData(FALSE);
		}
		/*else if (1000 != test.TestText(m_strFunction)) {
			AfxMessageBox(_T("함수가 아님"));
			return;
		}*/

	}
	else {//원
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
			return;
		}
		else {
			strIndex.Format(_T("%d"), m_nSelectedItem + 1);
			m_listFunction.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			CFunction1Dlg* pMain;
			pMain = (CFunction1Dlg*)AfxGetMainWnd();
			pMain->m_dlgSketch.m_listFunction1.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

			m_strFunction.Empty();

			pMain->m_nVaildSelected[m_nSelectedItem] = VAILD_ELLIPSE;

			pMain->UpdateData(FALSE);
		}
	}
	UpdateData(FALSE);
}


void CFunctionExDlg::OnItemchangedListFunction(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

	m_strFunction = m_listFunction.GetItemText(m_nSelectedItem, 1);
	
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);

	//UpdateData(FALSE);
	*pResult = 0;
}


void CFunctionExDlg::OnBnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_strFunction.Empty();
	if (!m_bLE) {
		CCreateDlg dlgCreate;
		if (dlgCreate.DoModal() == IDOK) {

		}
		dlgCreate.DestroyWindow();
	}
	else {
		CCreateEDlg dlgCreate_E;
		if (dlgCreate_E.DoModal() == IDOK) {

		}
		dlgCreate_E.DestroyWindow();
	}
}


//void CFunctionExDlg::OnClickListFunction(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	int s = pNMItemActivate->iItem;
//	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
//
//	m_listFunction.SetTextBkColor(pMain->m_color[m_nSelectedItem]);
//
//	*pResult = 0;
//}


void CFunctionExDlg::OnCustomdrawListFunction(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMCD;
	int iRow = (int)lplvcd->nmcd.dwItemSpec;
	switch (lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	case CDDS_ITEMPREPAINT:
		lplvcd->clrText = RGB(255, 255, 255);
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	case CDDS_SUBITEM|CDDS_PREPAINT|CDDS_ITEM:
		int i = iRow % 10;
		lplvcd->clrTextBk = pMain->m_color[i];
		*pResult = CDRF_DODEFAULT;
		return;
	}
	return;
	//이게 되네? ㅋㅋㅋㅋㅋㅋㅋ
}


void CFunctionExDlg::OnRadioLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bLE = false;

	//Ex) [ ]x^9+[ ]x^4+9x^2+[ ]x+[ ]
	GetDlgItem(IDC_STATIC_TEXT_FUNCTION)->SetWindowTextW(_T("Ex) []x^9+[]x^4+[]x^2+[]x+[]"));
}


void CFunctionExDlg::OnRadioEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bLE = true;

	//Ex) (x-[ ])^2+(y-[ ])^2/25
	GetDlgItem(IDC_STATIC_TEXT_FUNCTION)->SetWindowTextW(_T("Ex) (x-[])^2/[]+(y-[])^2/[]"));
}


BOOL CFunctionExDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetWindowRect(&rect);
	//pDC->FillSolidRect(0, 0, rect.Width(), rect.Height(), BKGND);

	return TRUE;
}


void CFunctionExDlg::OnClickedButtonOnoff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_nSelectedItem >= 0) {
		CFunction1Dlg* pMain;
		pMain = (CFunction1Dlg*)AfxGetMainWnd();

		pMain->m_bOnoff[m_nSelectedItem] = !pMain->m_bOnoff[m_nSelectedItem];
		if (pMain->m_bOnoff[m_nSelectedItem ]) {
			m_listFunction.SetItemText(m_nSelectedItem, 2, _T("보이기"));
			pMain->m_dlgSketch.m_listFunction1.SetItemText(m_nSelectedItem, 2, _T("보이기"));
		}
		else {
			m_listFunction.SetItemText(m_nSelectedItem, 2, _T("감추기"));
			pMain->m_dlgSketch.m_listFunction1.SetItemText(m_nSelectedItem, 2, _T("감추기"));
		}
		UpdateData(FALSE);
		pMain->m_dlgSketch.UpdateData(FALSE);
		pMain->OnMouseWheel(MK_CONTROL, 0, NULL);
	}
	else {
		AfxMessageBox(_T("아이템을 선택하지 않았습니다."));
	}
}
