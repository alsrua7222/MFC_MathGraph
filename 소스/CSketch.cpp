#include "pch.h"
#include "CSketch.h"
#include "Function_1Dlg.h"
#include "CFunctionProc.h"

CSketch::CSketch() {
	m_nID = 0;
	m_nXY = 1.0;
	//  m_strX = _T("");
	//  m_strY = _T("");
	m_nX = m_nY = 0.0;
	m_nEPWidth = 0;
	m_nEPHeight = 0;
	m_nSizeReal = 0;
	m_bDrag = false;
	m_nSize = 25;
}
CSketch::~CSketch() {

}
CSketch::CSketch(int nID) {
	m_nID = nID;
	m_nXY = 1.0;
	//  m_strX = _T("");
	//  m_strY = _T("");
	m_nX = m_nY = 0.0;
	m_nEPWidth = 0;
	m_nEPHeight = 0;
	m_nSizeReal = 0;
	m_bDrag = false;
	m_nSize = 25;
	m_ptX_First = m_ptX_Second = m_ptY_First = m_ptY_Second = 0;
}


void CSketch::Draw_Layout(int *nSizeWheel)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CDC* dc = pMain->m_staticView.GetWindowDC();
	CDC* dc2 = pMain->m_staticView.GetWindowDC();
	CDC* dc3 = pMain->m_staticView.GetWindowDC();
	CDC* dc4 = pMain->m_staticView.GetWindowDC();

	setRectViewSize(&m_rectView);
	setPointCenter(&m_ptCenter, &m_rectView);
	setLayoutSize(m_ptCenter, m_rectView);
	Draw_background(255, 255, 255);

	m_nXY = 1.0;
	m_nSize = m_nSizeReal = *nSizeWheel;
	while (true)
	{
		if (m_nSize > 50) {
			m_nSize -= 25;
			m_nXY = ValueChangedXY(m_nXY, TRUE);
		}
		else if (m_nSize < 25) {
			m_nSize += 25;
			m_nXY = ValueChangedXY(m_nXY, FALSE);
		}
		else {
			break;
		}
	}
	
	m_nEPWidth = (int)((double)(m_rectView.Width() / 2.0f) / (double) m_nSize);
	m_nEPHeight = (int)((double)(m_rectView.Height() / 2.0f) / (double)m_nSize);

	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;

	setMapMode_CENTER(dc, ZoomSize_W, ZoomSize_H);
	setMapMode_CENTER(dc2, ZoomSize_W, ZoomSize_H);
	setMapMode_CENTER(dc3, ZoomSize_W, ZoomSize_H);
	setMapMode_CENTER(dc4, ZoomSize_W, ZoomSize_H);

	CPen pen, * oldpen; //중간 검은색 선, dc
	CPen pen2, * oldpen2; //얇은 밝은 회색 선, dc2
	CPen pen3, * oldpen3; //두꺼운 검은색 선, dc3
	CPen pen4, * oldpen4; //얇은 어두운 회색 선, dc4

	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = dc->SelectObject(&pen);

	pen2.CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
	oldpen2 = dc2->SelectObject(&pen2);

	pen3.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	oldpen3 = dc3->SelectObject(&pen3);

	pen4.CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	oldpen4 = dc4->SelectObject(&pen4);

	dc3->MoveTo((int)-m_rectView.Width() / 2.0 - 50, 0);
	dc3->LineTo((int)m_rectView.Width() / 2.0 + 50, 0);
	dc3->MoveTo(0, (int)-m_rectView.Height() / 2.0 - 50);
	dc3->LineTo(0, (int)m_rectView.Height() / 2.0 + 50);

	CClientDC textureDC(pMain);
	CFont font;
	textureDC.SetBkMode(TRANSPARENT);
	font.CreatePointFont(200, _T("굴림체"));
	textureDC.SelectObject(font);
	textureDC.TextOutW(m_rectLayer.right - 30, m_ptCenter.y - 15, _T("X"));
	textureDC.TextOutW(m_ptCenter.x-15, m_rectLayer.top + 20, _T("Y"));
	font.DeleteObject();

	dc->SetBkMode(TRANSPARENT);

	int j = 1;
	for (int i = 1; i <= m_nSize; i++) {
		if (i%5 == 0) {
			m_nX = m_nXY * j;
			m_nY = m_nXY * j;
			j++;
			CString strX, strY;
			strX.Format(_T("%.2lf"), m_nX);
			strY.Format(_T("%.2lf"), -m_nY);
			dc->TextOutW(m_nEPWidth * i, 10, strX);
			dc->TextOutW(10, m_nEPHeight * i, strY);
			strX.Format(_T("%.2lf"), -m_nX);
			strY.Format(_T("%.2lf"), m_nY);
			dc->TextOutW(- m_nEPWidth * i, 10, strX);
			dc->TextOutW(10, - m_nEPHeight * i, strY);

			dc4->MoveTo(m_nEPWidth * i, -m_rectView.Height());
			dc4->LineTo(m_nEPWidth * i, m_rectView.Height());
			dc4->MoveTo(-m_nEPWidth * i, -m_rectView.Height());
			dc4->LineTo(-m_nEPWidth * i, m_rectView.Height());

			dc4->MoveTo(-m_rectView.Width(), m_nEPHeight * i);
			dc4->LineTo(m_rectView.Width(), m_nEPHeight * i);
			dc4->MoveTo(-m_rectView.Width(), -m_nEPHeight * i);
			dc4->LineTo(m_rectView.Width(), -m_nEPHeight * i);
		}
		else {
			dc2->MoveTo(m_nEPWidth * i, -m_rectView.Height());
			dc2->LineTo(m_nEPWidth * i, m_rectView.Height());
			dc2->MoveTo(-m_nEPWidth * i, -m_rectView.Height());
			dc2->LineTo(-m_nEPWidth * i, m_rectView.Height());

			dc2->MoveTo(-m_rectView.Width(), m_nEPHeight * i);
			dc2->LineTo(m_rectView.Width(), m_nEPHeight * i);
			dc2->MoveTo(-m_rectView.Width(), -m_nEPHeight * i);
			dc2->LineTo(m_rectView.Width(), -m_nEPHeight * i);
		}
	}

	//삭제다
	dc->SelectObject(oldpen);
	pen.DeleteObject();
	dc2->SelectObject(oldpen2);
	pen2.DeleteObject();
	dc3->SelectObject(oldpen3);
	pen3.DeleteObject();
	dc4->SelectObject(oldpen4);
	pen4.DeleteObject();
}


void CSketch::Draw_Line(FuncInfo_Line data, COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CDC* dc = pMain->m_staticView.GetWindowDC();

	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;

	setMapMode_CENTER(dc, ZoomSize_W, ZoomSize_H);

	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 3, color);
	oldpen = dc->SelectObject(&pen);

	int j = 1;
	bool bFirst = true;
	double y = 0;

	for (int x_Real = -ZoomSize_W/2.0; x_Real < ZoomSize_W/2.0; x_Real++) {//Layout에서 선 그리기
		y = 0;
		double x_per = x_Real / (double)ZoomSize_W * 100;
		double x = m_nX / 50.0 * x_per;

		for (int i = 0; i < 10; i++) {
			if (data.degree[i] == true) {
				y += data.coef[i] * pow(x, data.expo[i]);
			}
		}

		double y_per = y / (double) m_nY * 100.0;
		int y_Real = (int)-(ZoomSize_H / 100.0 * y_per);
		
		//if (!bFirst) x_Real--;
		if (50 >= y_per && y_per >= -50) {
			if (bFirst) {
				dc->MoveTo(x_Real, y_Real);
				bFirst = !bFirst;
			}
			else {
				dc->LineTo(x_Real, y_Real);
				//bFirst = !bFirst;
			}
		}
		else {
			bFirst = true;
		}
		
	}

	dc->SelectObject(oldpen);
	//dc->DeleteDC();
	pen.DeleteObject();
}

void CSketch::Draw_Ellipse(FuncInfo_Ellipse data, COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CDC* dc = pMain->m_staticView.GetWindowDC();
	//CDC* dc2 = pMain->m_staticView.GetWindowDC();
	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;

	setMapMode_CENTER(dc, ZoomSize_W, ZoomSize_H);
	/*
	dc2->SetMapMode(MM_ANISOTROPIC);
	dc2->SetWindowExt(m_rectView.Width(), m_rectView.Height());
	dc2->SetViewportExt(ZoomSize_W, ZoomSize_H);
	dc2->SetViewportOrg(m_ptCenter.x, m_ptCenter.y);
	*/
	CPen pen, * oldpen;
	//CPen * oldpen2;
	pen.CreatePen(PS_SOLID, 3, color);
	oldpen = dc->SelectObject(&pen);
	//oldpen2 = dc2->SelectObject(&pen);
	dc->SelectStockObject(NULL_BRUSH);

	double x1, x2, y1, y2; // 논리 값 = Elipse함수 활용
	int x1_Real, x2_Real, y1_Real, y2_Real; //물리 값 (-x-y, +x+y)
	double x1_per, x2_per, y1_per, y2_per; //퍼센트 값
	double sqrt_a, sqrt_b; //a와 b의 제곱근
	sqrt_a = sqrt(data.a);
	sqrt_b = sqrt(data.b);
	x1 = data.x - sqrt_a;
	x2 = data.x + sqrt_a;
	y1 = data.y + sqrt_b;
	y2 = data.y - sqrt_b;
	x1_per = x1 / (double)m_nX * 50.0;
	x2_per = x2 / (double)m_nX * 50.0;
	y1_per = y1 / (double)m_nY * 50.0;
	y2_per = y2 / (double)m_nY * 50.0;
	x1_Real = (int)(ZoomSize_W / 100.0 * x1_per);
	x2_Real = (int)(ZoomSize_W / 100.0 * x2_per);
	y1_Real = -(int)(ZoomSize_H / 100.0 * y1_per);
	y2_Real = -(int)(ZoomSize_H / 100.0 * y2_per);

	dc->Ellipse(x1_Real, y1_Real, x2_Real, y2_Real);
	/*
	double x, y_plus, y_minus;//경우의 수 3개.
	double x_per, y_plus_per, y_minus_per;
	int x_Real, y_plus_Real, y_minus_Real;

	bool bFirst, bFirst2;
	bFirst = bFirst2 = false;
	
	for (int i = x1_Real; i < x2_Real; i++) {
		x_per = i / (double)ZoomSize_W * 100.0;
		x = m_nX / 50.0 * x_per;// m_nX : x = 50% : x_per

		y_plus = sqrt(pow(data.radian, 2) - (pow(x - data.x, 2))) + data.y;
		y_minus = data.y - sqrt(pow(data.radian, 2) - (pow(x - data.x, 2)));
		y_plus_per = y_plus / (double)m_nY * 50.0;//m_nY : y = 50% : y_per
		y_minus_per = y_minus / (double)m_nY * 50.0;
		y_plus_Real = (int)-(ZoomSize_H / 100.0 * y_plus_per);// Height : y_Real = 100% : y_per
		y_minus_Real = (int)-(ZoomSize_H / 100.0 * y_minus_per);
		
		if (y_plus_per > -50 && y_plus_per < 50) {
			if (bFirst) {
				dc->MoveTo(i, y_plus_Real);
				bFirst = false;
			}
			else {
				dc->LineTo(i, y_plus_Real);
			}
			if (bFirst2) {
				dc2->MoveTo(i, y_minus_Real);
				bFirst2 = false;
			}
			else {
				dc2->LineTo(i, y_minus_Real);
			}
		}
		else {
			bFirst = true;
			bFirst2 = true;
		}
		
	}
	*/
	dc->SelectObject(oldpen);
	//dc2->SelectObject(&oldpen2);
	pen.DeleteObject();
}

void CSketch::setLayoutSize(CPoint ptCenter, CRect rectView)
{
	// TODO: 여기에 구현 코드 추가.
	m_rectLayer.left = ptCenter.x - (int)(rectView.Width() / 2.0f);
	m_rectLayer.right = ptCenter.x + (int)(rectView.Width() / 2.0f);
	m_rectLayer.top = ptCenter.y - (int)(rectView.Height() / 2.0f);
	m_rectLayer.bottom = ptCenter.y + (int)(rectView.Height() / 2.0f);
}


void CSketch::setRectViewSize(CRect* rectView)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	pMain->GetDlgItem(m_nID)->GetWindowRect(rectView);

}


void CSketch::setPointCenter(CPoint* ptCenter, CRect* rectView)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	*ptCenter = rectView->CenterPoint();
	pMain->ScreenToClient(ptCenter);
}


void CSketch::Draw_background(int nRed = 255, int nGreen = 255, int nBlue = 255)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();

	CClientDC dcBrush(pMain);
	CBrush brush, * oldbrush;
	brush.CreateSolidBrush(RGB(nRed, nGreen, nBlue));
	oldbrush = dcBrush.SelectObject(&brush);

	dcBrush.Rectangle(m_rectLayer);

	dcBrush.SelectObject(oldbrush);
	brush.DeleteObject();
}

/*
void CSketch::Draw_DivisionLine(CPoint ptCenter, CRect rectView, CClientDC dc , int* nSizeWheel)
{
	// TODO: 여기에 구현 코드 추가.
	//구분선
	for (int i = 0; i < *nSizeWheel; i++) {
		if (*nSizeWheel <= 20) {
			if (i % 2 == 0) {
				CString tmp_X, tmp_Y;
				tmp_X.Format(_T("%d"), i - *nSizeWheel / 2);
				tmp_Y.Format(_T("%d"), i - *nSizeWheel / 2);
				dc->TextOutW(m_rectLayer.left + 3 + ((rectView.Width() / (double)*nSizeWheel) * i), ptCenter.y - 15, tmp_X);
				dc->TextOutW(ptCenter.x + 15, m_rectLayer.top + 3 + ((rectView.Height() / (double)*nSizeWheel) * i), tmp_Y);
			}

			if (i % 5 != 0) {
				dc->MoveTo(m_rectLayer.left + ((rectView.Width() / (double)*nSizeWheel) * i), ptCenter.y - 10);
				dc->LineTo(m_rectLayer.left + ((rectView.Width() / (double)*nSizeWheel) * i), ptCenter.y + 10);

				dc->MoveTo(ptCenter.x - 10, m_rectLayer.top + ((rectView.Height() / (double)*nSizeWheel) * i));
				dc->LineTo(ptCenter.x + 10, m_rectLayer.top + ((rectView.Height() / (double)*nSizeWheel) * i));
			}
			else {
				dc3.MoveTo(m_rectLayer.left + ((rectView.Width() / (double)*nSizeWheel) * i), ptCenter.y - 10);
				dc3.LineTo(m_rectLayer.left + ((rectView.Width() / (double)*nSizeWheel) * i), ptCenter.y + 10);

				dc3.MoveTo(ptCenter.x - 10, m_rectLayer.top + ((rectView.Height() / (double)*nSizeWheel) * i));
				dc3.LineTo(ptCenter.x + 10, m_rectLayer.top + ((rectView.Height() / (double)*nSizeWheel) * i));
			}

		}
		else if (20 < *nSizeWheel && *nSizeWheel <= 40) {

		}
		else if (40 < *nSizeWheel && *nSizeWheel <= 60) {

		}
	}
}
*/

/*
void CSketch::setCreatePen(CClientDC *tDC,int nWidth, int nRed = 0 , int nGreen = 0, int nBlue = 0)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	
	CClientDC dc(pMain);
	CPen pen, * oldpen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	oldpen = dc->SelectObject(&pen);

	*tDC = dc;
}
*/

int CSketch::DoubleToLength1(double tmp)
{
	// TODO: 여기에 구현 코드 추가.
	int length = 0;
	while (true) {
		if (tmp < 1) break;
		tmp = tmp / 10;
		length++;
	}
	return length - 1;
}

int CSketch::DoubleToLength2(double tmp)
{
	// TODO: 여기에 구현 코드 추가.
	int length = 0;
	while (true) {
		if (tmp >= 1) break;
		tmp = tmp * 10;
		length++;
	}
	return length;
}

double CSketch::ValueChangedXY(double nXY, bool updown)
{
	// TODO: 여기에 구현 코드 추가.
	int length;
	double Max_order = nXY;
	if (nXY >= 1) {
		length = DoubleToLength1(nXY);
		for (int i = 0; i < length; i++) {
			Max_order = Max_order / 10;
		}
	}
	else {
		length = DoubleToLength2(nXY);
		for (int i = 0; i < length; i++) {
			Max_order = Max_order * 10;
		}
	}
	int choice = Max_order;
	bool spec = false; //special
	switch (choice)
	{
	case 1:
		if (updown) {
			Max_order = 2;
		}
		else {
			Max_order = 5;
			if (nXY >= 1) {
				nXY = nXY / 10.0;
				spec = true;
			}
			else length++;
		}
		break;
	case 2:
		if (updown) {
			Max_order = 5;
		}
		else {
			Max_order = 1;
		}
		break;
	case 5:
		if (updown) {
			Max_order = 1;
			if (nXY < 1) nXY = nXY * 10.0;
			else length++;
		}
		else {
			Max_order = 2;
		}
		break;
	default:
		break;
	}

	double resultXY;

	if (nXY >= 1) {
		resultXY = Max_order * pow(10, length);
	}
	else {
		if (spec == true && nXY == 0.1) {
			resultXY = Max_order * pow(10, -(length + 1));
		}
		else resultXY = Max_order * pow(10, -length);
	}

	return resultXY;
}




void CSketch::Sketch_Line(FuncInfo_Line* data, int nSelMode, bool* bLBDown, CPoint point, COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CDC* dc = pMain->m_staticView.GetWindowDC();
	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;

	setMapMode_CENTER(dc, ZoomSize_W, ZoomSize_H);

	CPen pen, * oldpen;
	if (nSelMode == 1) {//MouseMove
		pen.CreatePen(PS_SOLID, 1, color);
		oldpen = dc->SelectObject(&pen);
		dc->SetROP2(R2_NOTXORPEN);
		if (*bLBDown) {
			CPoint tmpStart, tmpPrev, tmpPoint;
			tmpStart.x = m_ptStart.x - m_ptCenter.x;
			tmpStart.y = m_ptStart.y - m_ptCenter.y;
			tmpPrev.x = m_ptPrev.x - m_ptCenter.x;
			tmpPrev.y = m_ptPrev.y - m_ptCenter.y;
			tmpPoint.x = point.x - m_ptCenter.x;
			tmpPoint.y = point.y - m_ptCenter.y;
			dc->MoveTo(tmpStart);
			dc->LineTo(tmpPrev);
			dc->MoveTo(tmpStart);
			dc->LineTo(tmpPoint);
			m_ptPrev = point;
		}
		dc->SelectObject(oldpen);
	}
	else if (nSelMode == 2) {//LButtonDown
		//m_ptStart = m_ptPrev = 0;
		m_ptStart = m_ptPrev = point;
		*bLBDown = !*bLBDown;
		if (*bLBDown) {
			int x_Real = point.x - m_ptCenter.x;
			int y_Real = point.y - m_ptCenter.y;
			CFunctionProc Proc;
			m_ptX_First = Proc.LogicToPhysicalValue(true, x_Real, x_Real, 
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			m_ptY_First = Proc.LogicToPhysicalValue(false, x_Real, y_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
		}
		else {
			CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
			int x_Real = point.x - m_ptCenter.x;
			int y_Real = point.y - m_ptCenter.y;
			CFunctionProc Proc;
			m_ptX_Second = Proc.LogicToPhysicalValue(true, x_Real, x_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			m_ptY_Second = Proc.LogicToPhysicalValue(false, x_Real, y_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			Proc.SketchToData_L(m_ptX_First, m_ptY_First, m_ptX_Second, m_ptY_Second, &pMain->m_info_L);
			CString str;
			Proc.DataToCString_L(pMain->m_info_L, str);
			pMain->m_dlgSketch.m_strFunction = str;
			pMain->m_dlgSketch.UpdateData(FALSE);
			pMain->m_dlgSketch.OnBnClickedButtonAdd();
			Draw_Line(pMain->m_info_L, color);
		}
	}
	else if (nSelMode == 3) {//LButtonUp
		//*bDrag = false;
	}
	else if (nSelMode == 4) {//RButtonDown

	}
	else if (nSelMode == 5) {//nChar = VK_ESCKEY

	}
	pen.DeleteObject();
}


void CSketch::Sketch_CursurPos(bool onoff, CString &strX, CString &strY, CPoint point)
{
	// TODO: 여기에 구현 코드 추가.
	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;
	if (onoff) {

		CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
		CClientDC dc(pMain);

		int x_point = m_ptCenter.x - point.x;
		int y_point = m_ptCenter.y - point.y;
	
		int x_Real = x_point;
		double x_per = x_Real / (double)ZoomSize_W * 100;
		double x = -m_nX / 50.0 * x_per;

		int y_Real = y_point;
		double y_per = y_Real / (double)ZoomSize_H * 100;
		double y = m_nY / 50.0 * y_per;

		strX.Format(_T("%.3lf"), x);
		strY.Format(_T("%.3lf"), y);
	}
}


void CSketch::Sketch_Ellipse(FuncInfo_Ellipse* data, int nSelMode, bool* bLBDown, CPoint point, COLORREF color)
{
	// TODO: 여기에 구현 코드 추가.
	CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
	CDC* dc = pMain->m_staticView.GetWindowDC();
	int ZoomSize_W = m_rectView.Width() + m_nSize * 2;
	int ZoomSize_H = m_rectView.Height() + m_nSize * 2;

	setMapMode_CENTER(dc, ZoomSize_W, ZoomSize_H);

	CPen pen, * oldpen;
	if (nSelMode == 1) {//MouseMove
		pen.CreatePen(PS_SOLID, 1, color);
		oldpen = dc->SelectObject(&pen);
		dc->SetROP2(R2_NOTXORPEN);
		if (*bLBDown) {
			CPoint tmpStart, tmpPrev, tmpPoint;
			tmpStart.x = m_ptStart.x - m_ptCenter.x;
			tmpStart.y = m_ptStart.y - m_ptCenter.y;
			tmpPrev.x = m_ptPrev.x - m_ptCenter.x;
			tmpPrev.y = m_ptPrev.y - m_ptCenter.y;
			tmpPoint.x = point.x - m_ptCenter.x;
			tmpPoint.y = point.y - m_ptCenter.y;

			dc->Ellipse(tmpStart.x, tmpStart.y, tmpPrev.x, tmpPrev.y);
			dc->Ellipse(tmpStart.x, tmpStart.y, tmpPoint.x, tmpPoint.y);

			m_ptPrev = point;
		}
		dc->SelectObject(oldpen);
	}
	else if (nSelMode == 2) {//LButtonDown
		//m_ptStart = m_ptPrev = 0;
		m_ptStart = m_ptPrev = point;
		*bLBDown = !*bLBDown;
		if (*bLBDown) {
			int x_Real = point.x - m_ptCenter.x;
			int y_Real = point.y - m_ptCenter.y;
			CFunctionProc Proc;
			m_ptX_First = Proc.LogicToPhysicalValue(true, x_Real, x_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			m_ptY_First = Proc.LogicToPhysicalValue(false, x_Real, y_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
		}
		else {
			CFunction1Dlg* pMain = (CFunction1Dlg*)AfxGetMainWnd();
			int x_Real = point.x - m_ptCenter.x;
			int y_Real = point.y - m_ptCenter.y;
			CFunctionProc Proc;
			m_ptX_Second = Proc.LogicToPhysicalValue(true, x_Real, x_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			m_ptY_Second = Proc.LogicToPhysicalValue(false, x_Real, y_Real,
				m_nX, m_nY, ZoomSize_W, ZoomSize_H);
			Proc.SketchToData_E(m_ptX_First, m_ptY_First, m_ptX_Second, m_ptY_Second, &pMain->m_info_E);
			
			CString str;
			Proc.DataToCString_E(pMain->m_info_E, str);
			pMain->m_dlgSketch.m_strFunction = str;
			pMain->m_dlgSketch.UpdateData(FALSE);
			pMain->m_dlgSketch.OnBnClickedButtonAdd();
			Draw_Ellipse(pMain->m_info_E, color);
		}
	}
	else if (nSelMode == 3) {//LButtonUp
		//*bDrag = false;
	}
	else if (nSelMode == 4) {//RButtonDown

	}
	else if (nSelMode == 5) {//nChar = VK_ESCKEY

	}
	pen.DeleteObject();

}


void CSketch::setMapMode_CENTER(CDC* dc, int ZoomSize_W, int ZoomSize_H)
{
	// TODO: 여기에 구현 코드 추가.
	dc->SetMapMode(MM_ANISOTROPIC);
	dc->SetWindowExt(m_rectView.Width(), m_rectView.Height());
	dc->SetViewportExt(ZoomSize_W, ZoomSize_H);
	dc->SetViewportOrg(m_ptCenter.x, m_ptCenter.y);
}
