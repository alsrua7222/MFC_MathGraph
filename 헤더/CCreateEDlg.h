#pragma once


// CCreateEDlg 대화 상자

class CCreateEDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCreateEDlg)

public:
	CCreateEDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCreateEDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CREATE_E };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	double m_nX;
	double m_nY;
	double m_nB;
	double m_nA;
	afx_msg void OnBnClickedButtonOk();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
