#pragma once


// CBMPButton

class CBMPButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CBMPButton)

public:
	CBMPButton();
	virtual ~CBMPButton();

protected:
	DECLARE_MESSAGE_MAP()

public:

	BOOL AutoLoad(UINT nID, CWnd* pParent);
	void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};


