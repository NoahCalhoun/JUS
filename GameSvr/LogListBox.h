#pragma once

#include <CommCtrl.h>

class CLogListBox
{
public:
	CLogListBox();
	virtual ~CLogListBox();

private:
	HWND m_hWnd;

	HFONT m_hFont;
	INT m_iCurIdx;
	INT m_iMaxLen;

public:
	HWND CreateListBox(HWND _hwndParent);

	void AddString(STRING _str);
	void SetHScroll(STRING _str);
};

