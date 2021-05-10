
// Function_1Dlg.h: 헤더 파일
//

#pragma once
#include "CFunctionExDlg.h"
#include "CSketchDlg.h"
#include "CHelpDlg.h"
#include "CTitleDlg.h"
#include "CBMPButton.h"
#define INDEX 10
#define BKGND RGB(100, 100, 100)
enum { VAILD_NOPE, VAILD_LINE, VAILD_ELLIPSE };
// CFunction1Dlg 대화 상자
class CFunction1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CFunction1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FUNCTION_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool m_onoff;
	CTabCtrl m_tabSelection;
	CFunctionExDlg m_dlgFunctionEx;
	CSketchDlg m_dlgSketch;
	afx_msg void OnSelchangeTabSelection(NMHDR* pNMHDR, LRESULT* pResult);
	struct FuncInfo_Line {
		bool degree[INDEX];
		int expo[INDEX];
		double coef[INDEX];
	};
	struct FuncInfo_Ellipse {
		double x;
		double y;
		double a;
		double b;
	};
	struct FuncInfo_Line m_info_L;
	struct FuncInfo_Ellipse m_info_E;
	CStatic m_staticView;
	void UpdateDrawing();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	int m_nSizeWheel;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool m_bDragDown;
	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bLBDown;
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	bool m_bRBDown;
	class CSketch* s;
//	afx_msg void OnBnClickedButtonAllonoff();
//	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//	afx_msg void OnNcPaint();
	
	COLORREF m_color[10];
	int m_nVaildSelected[10]; //0=없음, 1=직선, 2=원
	bool m_bOnoff[10];
	bool m_bFirst;
	afx_msg void OnClickedButtonHelp();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonReset();
	CBMPButton m_btnHelp;
	CBMPButton m_btnReset;
	CBMPButton m_btnHideShow;
	CBMPButton m_btnSave;
	CBMPButton m_btnLoad;
	CString m_strX;
	CString m_strY;
	CStatic m_staticX;
	CStatic m_staticY;
	afx_msg void OnBnClickedButtonHideshow();
	bool m_bFirst2;
};
