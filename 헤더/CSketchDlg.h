#pragma once
#include "CBMPButton.h"

// CSketchDlg 대화 상자

class CSketchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSketchDlg)

public:
	CSketchDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSketchDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SKETCH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listFunction1;
	CString m_strFunction;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnCustomdrawListFunction(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedRadioLine();
	bool m_bLE;
	afx_msg void OnBnClickedRadioEllipse();
	afx_msg void OnBnClickedButtonDraw();
	bool m_bDrawing;
	CBMPButton m_btnDrawing;
	afx_msg void OnItemchangedListFunction(NMHDR* pNMHDR, LRESULT* pResult);
	int m_nSelectedItem;
	afx_msg void OnClickedButtonOnoff();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnClickedButtonModify();
};
