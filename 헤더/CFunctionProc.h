#pragma once
#include "CSketch.h"
class CFunctionProc :
	public CSketch
{
public:
	CFunctionProc();
	virtual ~CFunctionProc();
	
	void SketchToData_L(double x1, double y1, double x2, double y2, FuncInfo_Line* data);
	void SketchToData_E(double x1, double y1, double x2, double y2, FuncInfo_Ellipse* data);
	void StrToData_L(CString str, FuncInfo_Line* data);
	char* CStringToChar(CString& str);
	double LogicToPhysicalValue(bool xy, int x_Real, int y_Real, double x_Max, double y_Max, int SizeW, int SizeH);
	void StrToData_E(CString str, FuncInfo_Ellipse* data);
	void DataToCString_L(FuncInfo_Line data, CString &str);
	void DataToCString_E(FuncInfo_Ellipse data, CString &str);
};

