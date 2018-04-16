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
	void Clear(void);

	void AddString(const STRING& _str);

private:
	void SetHScroll(const STRING& _str);
};

