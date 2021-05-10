// DataBase.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "DataBase.h"


// DataBase

IMPLEMENT_DYNAMIC(DataBase, CWnd)

DataBase::DataBase()
{
	file = new CStdioFile();
}

DataBase::~DataBase()
{
}


BEGIN_MESSAGE_MAP(DataBase, CWnd)
END_MESSAGE_MAP()



// DataBase 메시지 처리기




void DataBase::DBOpen_txt(int mode)
{
	// TODO: 여기에 구현 코드 추가.
	if (mode == SAVE) {
		CTime cTime = CTime::GetCurrentTime();
		CString name = _T("Save_");
		CString tmp = _T("");
		tmp.Format(_T("%2d%2d%2d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		name += tmp + _T(".txt");
		file->Open(name, CFile::modeCreate | CFile::modeWrite);
	}
	else {
		CFileDialog dlg(TRUE, _T("*.txt"));
		if (dlg.DoModal() == IDOK) {
			CString fileName = dlg.GetFileName();
			CString filePath = dlg.GetPathName();
			file->SetFilePath(filePath);
			file->Open(fileName, CFile::modeRead);
		}
	}
}


void DataBase::DBClose_txt()
{
	// TODO: 여기에 구현 코드 추가.
	file->Close();
}


void DataBase::DBSave_txt(CString str)
{
	// TODO: 여기에 구현 코드 추가.
	DBOpen_txt(SAVE);
	file->WriteString(str);
	AfxMessageBox(_T("세이브 완료"), MB_OK | MB_ICONWARNING);
	DBClose_txt();
}


void DataBase::DBLoad_txt(CString &str)
{
	// TODO: 여기에 구현 코드 추가.
	CString tmp;
	DBOpen_txt(LOAD);
	while (file->ReadString(tmp)) {
		str += tmp + _T("\n");
	}
	AfxMessageBox(_T("로드 완료"), MB_OK | MB_ICONWARNING);
	DBClose_txt();
}
