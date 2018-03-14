#include "stdafx.h"
#include "LogListBox.h"


CLogListBox::CLogListBox()
{
}

CLogListBox::~CLogListBox()
{
}

HWND CLogListBox::CreateListBox(HWND _hwndParent)
{
	if (!_hwndParent) return NULL;

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(_hwndParent, &rcClient);

	HMENU empty = HMENU();

	INT iW = (rcClient.right - rcClient.left) / 4;
	INT iH = rcClient.bottom - rcClient.top;

	m_hWnd = CreateWindow(WC_LISTBOX,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL |
		LBS_NOSEL,
		iW, 0,
		iW * 3, iH,
		_hwndParent,
		empty,
		g_hInst,
		NULL);

	for (size_t i = 0; i < 100; i++)
	{
	}

	return m_hWnd;
}

void CLogListBox::AddString(wstring _str)
{
	SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)_str.c_str());
}
