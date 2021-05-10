#pragma once

#include "Function_1Dlg.h"

class CSketch : public CFunction1Dlg
{
public:
	CSketch();
	virtual ~CSketch();
	CSketch(int nID);
	void Draw_Layout(int* nSizeWheel);
	void Draw_Line(FuncInfo_Line data, COLORREF color);
	void Draw_Ellipse(FuncInfo_Ellipse data, COLORREF color);
	void Draw_background(int nRed, int nGreen, int nBlue);
	void Sketch_Line(FuncInfo_Line *data, int nSelMode, bool *bLBDown, CPoint point, COLORREF color);
	void Sketch_Ellipse(FuncInfo_Ellipse* data, int nSelMode, bool *bLBDown, CPoint point, COLORREF color);
	void Sketch_CursurPos(bool onoff, CString &strX, CString &strY, CPoint point);
	void setLayoutSize(CPoint ptCenter, CRect rectView);
	void setRectViewSize(CRect* rectView);
	void setPointCenter(CPoint* ptCenter, CRect* rectView);
	void setMapMode_CENTER(CDC* dc, int ZoomSize_W, int ZoomSize_H);
	int DoubleToLength1(double tmp);
	int DoubleToLength2(double tmp);
	double ValueChangedXY(double nXY, bool updown);
	CRect m_rectLayer;
	CRect m_rectView;
	CPoint m_ptStart;
	CPoint m_ptPrev;
	CPoint m_ptCenter;
//	CString m_strX;
//	CString m_strY;
	bool m_bDrag;
	int m_nID;
	int m_nSize;
	int m_nEPWidth;
	int m_nEPHeight;
	int m_nSizeReal;
	double m_nXY;
	double m_nX;
	double m_nY;
	double m_nX_ViewSize;
	double m_nY_ViewSize;
	double m_ptX_First;
	double m_ptY_First;
	double m_ptX_Second;
	double m_ptY_Second;
};

