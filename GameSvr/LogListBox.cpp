#include "stdafx.h"
#include "LogListBox.h"


CLogListBox::CLogListBox()
	: m_iCurIdx(0)
	, m_iMaxLen(0)
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
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL,
		iW, 0,
		iW * 3, iH,
		_hwndParent,
		empty,
		g_hInst,
		NULL);

	m_hFont = CreateFont(16, 0, 0, 0
		, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET
		, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY
		, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	SendMessage(m_hWnd, WM_SETFONT, (WPARAM)m_hFont, 0);

	return m_hWnd;
}

void CLogListBox::AddString(const STRING& _str)
{
	if (m_iCurIdx > LOGLISTBOX_LOG_COUNT_MAX) {
		SendMessage(m_hWnd, LB_DELETESTRING, 0, 0);
		m_iCurIdx--;
	}

	SendMessage(m_hWnd, LB_ADDSTRING, 0, (LPARAM)_str.c_str());
	SendMessage(m_hWnd, LB_SETTOPINDEX, m_iCurIdx++, 0);

	SetHScroll(_str);
}

void CLogListBox::SetHScroll(const STRING& _str)
{
	SIZE sz = { 0, };
	HDC hdc = GetDC(m_hWnd);
	SelectObject(hdc, m_hFont);
	GetTextExtentPoint(hdc, _str.c_str(), (INT)_str.length() + 1, &sz);
	ReleaseDC(m_hWnd, hdc);

	m_iMaxLen = max(sz.cx, m_iMaxLen);
	SendMessage(m_hWnd, LB_SETHORIZONTALEXTENT, m_iMaxLen, 0);
}
