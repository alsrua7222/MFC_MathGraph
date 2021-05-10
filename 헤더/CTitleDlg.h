#pragma once


// CTitleDlg 대화 상자

class CTitleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTitleDlg)

public:
	CTitleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTitleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TITLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
//	afx_msg void OnBnClickedOk();
	void Destroy();
	void CreateShow();
	bool m_bFirst;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
