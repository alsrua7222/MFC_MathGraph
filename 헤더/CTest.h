#pragma once
#include "Function_1Dlg.h"

// CTest

class CTest : public CWnd
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest();
	virtual ~CTest();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int TestText(CString str);
	int CGetDegree(char* str);
	//int CCut(char* str, int pos, int* expo);
	CString CErrorCode(int errorcode);
	void toString_MSG(CFunction1Dlg::FuncInfo_Line* info);
	bool TestText_E(CString str);
};


