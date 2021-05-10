#pragma once


// CCreateDlg 대화 상자

class CCreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateDlg)

public:
	CCreateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCreateDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nX0;
	int m_nX1;
	int m_nX2;
	int m_nX3;
	int m_nX4;
	int m_nX5;
	int m_nX6;
	int m_nX7;
	int m_nX8;
	int m_nX9;

	virtual BOOL OnInitDialog();
	afx_msg void OnClickedCheckX0();
	afx_msg void OnClickedCheckX1();
	afx_msg void OnClickedCheckX2();
	afx_msg void OnClickedCheckX3();
	afx_msg void OnClickedCheckX4();
	afx_msg void OnClickedCheckX5();
	afx_msg void OnClickedCheckX6();
	afx_msg void OnClickedCheckX7();
	afx_msg void OnClickedCheckX8();
	afx_msg void OnClickedCheckX9();
	BOOL m_checkX0;
	BOOL m_checkX1;
	BOOL m_checkX2;
	BOOL m_checkX3;
	BOOL m_checkX4;
	BOOL m_checkX5;
	BOOL m_checkX6;
	BOOL m_checkX7;
	BOOL m_checkX8;
	BOOL m_checkX9;
	//	CString m_comboX0;
	CString m_comboX1;
	CString m_comboX2;
	CString m_comboX3;
	CString m_comboX4;
	CString m_comboX5;
	CString m_comboX6;
	CString m_comboX7;
	CString m_comboX8;
	CString m_comboX9;
	afx_msg void OnBnClickedOk();
	CString m_strFunction;
};
