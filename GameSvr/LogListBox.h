#pragma once

#include <CommCtrl.h>

class CLogListBox
{
public:
	CLogListBox();
	virtual ~CLogListBox();

private:
	HWND m_hWnd;

public:
	HWND CreateListBox(HWND _hwndParent);

	void AddString(wstring _str);
};

