// CSketchDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CSketchDlg.h"
#include "afxdialogex.h"
#include "CFunctionExDlg.h"
#include "Function_1Dlg.h"
#include "CTest.h"
#include "CSketch.h"


// CSketchDlg 대화 상자

IMPLEMENT_DYNAMIC(CSketchDlg, CDialogEx)

CSketchDlg::CSketchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SKETCH, pParent)
	, m_strFunction(_T(""))
{
	m_bDrawing = false;
	m_bLE = false;
}

CSketchDlg::~CSketchDlg()
{
}

void CSketchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FUNCTION, m_listFunction1);
	DDX_Text(pDX, IDC_EDIT_EXAM, m_strFunction);
	DDX_Control(pDX, IDC_BUTTON_DRAW, m_btnDrawing);
}


BEGIN_MESSAGE_MAP(CSketchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CSketchDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_FUNCTION, &CSketchDlg::OnCustomdrawListFunction)
	ON_BN_CLICKED(IDC_RADIO_LINE, &CSketchDlg::OnBnClickedRadioLine)
	ON_BN_CLICKED(IDC_RADIO_ELLIPSE, &CSketchDlg::OnBnClickedRadioEllipse)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CSketchDlg::OnBnClickedButtonDraw)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FUNCTION, &CSketchDlg::OnItemchangedListFunction)
	ON_BN_CLICKED(IDC_BUTTON_ONOFF, &CSketchDlg::OnClickedButtonOnoff)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CSketchDlg::OnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CSketchDlg::OnClickedButtonModify)
END_MESSAGE_MAP()


// CSketchDlg 메시지 처리기


BOOL CSketchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_btnDrawing.LoadBitmaps(IDB_BITMAP_Drawing_1, IDB_BITMAP_Drawing_2, IDB_BITMAP_Drawing_3, IDB_BITMAP_Drawing_4);

	CRect rect;
	GetDlgItem(IDC_LIST_FUNCTION)->GetClientRect(&rect);
	int W = rect.Width();
	int w[3];
	w[0] = (int)W * 15 / 100.0;
	w[1] = (int)W * 60 / 100.0;
	w[2] = W - w[0] - w[1];
	LPWSTR list[3] = { _T("번호"),_T("함수식"),_T("보이기/감추기") };
	int nWidth[3] = { w[0], w[1], w[2] };

	for (int i = 0; i < 3; i++) {
		m_listFunction1.InsertColumn(i, list[i], LVCFMT_CENTER, nWidth[i]);
	}
	m_listFunction1.SetExtendedStyle(m_listFunction1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_bLE = false;
	((CButton*)GetDlgItem(IDC_RADIO_LINE))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSketchDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int m_nCount = m_listFunction1.GetItemCount();

	//요소가 10개밖에 지원못함. 그러므로 삭제.
	if (m_nCount >= 10) return;
	CFunction1Dlg* pMain;
	pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CString strCount;
	CTest test;
	CFunction1Dlg* pFunc;
	UpdateData(TRUE);

	if (!m_bLE) {//직선
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
		}
		else{
			//else if (1000 == test.TestText(m_strFunction)) {
			strCount.Format(_T("%d"), m_nCount + 1);
			m_listFunction1.InsertItem(m_nCount, strCount);
			m_listFunction1.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			m_listFunction1.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			pMain->m_dlgFunctionEx.m_listFunction.InsertItem(m_nCount, strCount);
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
			pMain->m_bOnoff[m_nCount] = true;
			pMain->m_nVaildSelected[m_nCount] = VAILD_LINE;
			m_strFunction.Empty();
			pMain->UpdateData(FALSE);
			UpdateData(FALSE);
		}
		//else if (1000 != test.TestText(m_strFunction)) {
		//	AfxMessageBox(_T("함수가 아님"));
		//}
		return;
	}
	else {//원
		if (m_strFunction.IsEmpty()) {
			AfxMessageBox(_T("EMPTY"));
		}
		else {
			//else if (1000 == test.TestText(m_strFunction)) {
			strCount.Format(_T("%d"), m_nCount + 1);
			m_listFunction1.InsertItem(m_nCount, strCount);
			m_listFunction1.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			m_listFunction1.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			pMain->m_dlgFunctionEx.m_listFunction.InsertItem(m_nCount, strCount);
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nCount, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nCount, 2, LVIF_TEXT, _T("보이기"), 0, 0, 0, 0);
			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
		//	((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
			pMain->m_bOnoff[m_nCount] = true;
			pMain->m_nVaildSelected[m_nCount] = VAILD_ELLIPSE;
			m_strFunction.Empty();
			pMain->UpdateData(FALSE);
			UpdateData(FALSE);
		}
		return;
	}
	
}


void CSketchDlg::OnCustomdrawListFunction(NMHDR* pNMHDR, LRESULT* pResult)
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
	case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
		int i = iRow % 10;
		lplvcd->clrTextBk = pMain->m_color[i];
		*pResult = CDRF_DODEFAULT;
		return;
	}
	return;
}


void CSketchDlg::OnBnClickedRadioLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bLE = false;
}


void CSketchDlg::OnBnClickedRadioEllipse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bLE = true;
}


void CSketchDlg::OnBnClickedButtonDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	if (!m_bDrawing) {
		m_bDrawing = true;
		m_btnDrawing.LoadBitmaps(IDB_BITMAP_Drawing_Cancle_1, IDB_BITMAP_Drawing_Cancle_2, IDB_BITMAP_Drawing_Cancle_3, IDB_BITMAP_Drawing_Cancle_4);
	}
	else {
		m_bDrawing = false;
		m_btnDrawing.LoadBitmaps(IDB_BITMAP_Drawing_1, IDB_BITMAP_Drawing_2, IDB_BITMAP_Drawing_3, IDB_BITMAP_Drawing_4);
	}
	

}


void CSketchDlg::OnItemchangedListFunction(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nSelectedItem = pNMLV->iItem;

	m_strFunction = m_listFunction1.GetItemText(m_nSelectedItem, 1);

	((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(TRUE);
	//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(TRUE);
	*pResult = 0;
}


void CSketchDlg::OnClickedButtonOnoff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_nSelectedItem >= 0) {
		CFunction1Dlg* pMain;
		pMain = (CFunction1Dlg*)AfxGetMainWnd();

		pMain->m_bOnoff[m_nSelectedItem] = !pMain->m_bOnoff[m_nSelectedItem];
		if (pMain->m_bOnoff[m_nSelectedItem]) {
			m_listFunction1.SetItemText(m_nSelectedItem, 2, _T("보이기"));
			pMain->m_dlgFunctionEx.m_listFunction.SetItemText(m_nSelectedItem, 2, _T("보이기"));
		}
		else {
			m_listFunction1.SetItemText(m_nSelectedItem, 2, _T("감추기"));
			pMain->m_dlgFunctionEx.m_listFunction.SetItemText(m_nSelectedItem, 2, _T("감추기"));
		}
		UpdateData(FALSE);
		pMain->m_dlgFunctionEx.UpdateData(FALSE);
		pMain->OnMouseWheel(MK_CONTROL, 0, NULL);
	}
	else {
		AfxMessageBox(_T("아이템을 선택하지 않았습니다."));
	}
}


void CSketchDlg::OnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_nSelectedItem >= 0) {
		CFunction1Dlg* pMain;
		pMain = (CFunction1Dlg*)AfxGetMainWnd();
		int count = m_listFunction1.GetItemCount();
		m_listFunction1.DeleteItem(m_nSelectedItem);

		for (int i = m_nSelectedItem - 1; i < m_listFunction1.GetItemCount(); i++) {
			if (i == 9) {
				break;
			}
			CString strIndex;
			strIndex.Format(_T("%d"), i + 1);
			m_listFunction1.SetItemText(i, 0, strIndex);
			pMain->m_nVaildSelected[i] = pMain->m_nVaildSelected[i + 1];
			pMain->m_bOnoff[i] = pMain->m_bOnoff[i + 1];
		}
		pMain->m_nVaildSelected[count - 1] = VAILD_NOPE;
		pMain->m_bOnoff[count - 1] = false;
		m_strFunction.Empty();


		pMain->m_dlgFunctionEx.m_listFunction.DeleteItem(m_nSelectedItem);
		pMain->m_dlgFunctionEx.UpdateData(FALSE);

		for (int i = m_nSelectedItem - 1; i < pMain->m_dlgFunctionEx.m_listFunction.GetItemCount(); i++) {
			if (i == 9) {
				break;
			}
			CString strIndex;

			strIndex.Format(_T("%d"), i + 1);
			pMain->m_dlgFunctionEx.m_listFunction.SetItemText(i, 0, strIndex);
		}

		((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
		//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);
		pMain->OnMouseWheel(MK_CONTROL, 0, NULL);
	}
	else {
		AfxMessageBox(_T("아이템을 선택하지 않았습니다."));
	}

}


void CSketchDlg::OnClickedButtonModify()
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
			m_listFunction1.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			CFunction1Dlg* pMain;
			pMain = (CFunction1Dlg*)AfxGetMainWnd();
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
//			((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

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
			m_listFunction1.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			CFunction1Dlg* pMain;
			pMain = (CFunction1Dlg*)AfxGetMainWnd();
			pMain->m_dlgFunctionEx.m_listFunction.SetItem(m_nSelectedItem, 1, LVIF_TEXT, m_strFunction, 0, 0, 0, 0);

			((CButton*)GetDlgItem(IDC_BUTTON_DELETE))->EnableWindow(FALSE);
			((CButton*)GetDlgItem(IDC_BUTTON_ONOFF))->EnableWindow(FALSE);
			//((CButton*)GetDlgItem(IDC_BUTTON_MODIFY))->EnableWindow(FALSE);

			m_strFunction.Empty();

			pMain->m_nVaildSelected[m_nSelectedItem] = VAILD_ELLIPSE;

			pMain->UpdateData(FALSE);
		}
	}
	UpdateData(FALSE);
}
