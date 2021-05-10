#pragma once
#include "CBMPButton.h"
// CHelpDlg 대화 상자

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHelpDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool m_bFirst;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonUndo();
	int m_nStage;
//	CBitmapButton m_btnUndo;
//	CBitmapButton m_btnRedo;
	afx_msg void OnBnClickedButtonRedo();
//	CMFCButton m_btnAgo;
//	CMFCButton m_btnNext;
	CBMPButton m_btnAgo;
	CBMPButton m_btnNext;
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonAgo();
	CRect m_rectNext;
};
