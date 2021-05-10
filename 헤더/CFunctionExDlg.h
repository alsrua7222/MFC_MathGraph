#pragma once


// CFunctionExDlg 대화 상자

class CFunctionExDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFunctionExDlg)

public:
	CFunctionExDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFunctionExDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FUNCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFunction;
	CListCtrl m_listFunction;
	afx_msg void OnClickedButtonAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonDelete();
	int m_nSelectedItem;
	afx_msg void OnClickedButtonModify();
	afx_msg void OnItemchangedListFunction(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonOpen();
//	afx_msg void OnClickListFunction(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawListFunction(NMHDR* pNMHDR, LRESULT* pResult);
	bool m_bLE;
	afx_msg void OnRadioLine();
	afx_msg void OnRadioEllipse();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClickedButtonOnoff();
};
