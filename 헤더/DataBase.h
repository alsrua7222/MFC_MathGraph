#pragma once
#define SAVE 0
#define LOAD 1

// DataBase

class DataBase : public CWnd
{
	DECLARE_DYNAMIC(DataBase)

public:
	DataBase();
	virtual ~DataBase();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void DBOpen_txt(int mode);
	void DBClose_txt();
	void DBSave_txt(CString str);
	void DBLoad_txt(CString &str);
	CStdioFile* file;
};


