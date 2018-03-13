#include "stdafx.h"
#include "LogCategoryListView.h"
 

LogCategoryListView::LogCategoryListView()
{
}

LogCategoryListView::~LogCategoryListView()
{
}

HWND LogCategoryListView::CreateListView(HWND _hwndParent)
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(_hwndParent, &rcClient);

	HMENU empty = HMENU();

	INT iW = (rcClient.right - rcClient.left) / 4;
	INT iH = rcClient.bottom - rcClient.top;
	// Create the list-view window in report view with label editing enabled.
	m_hWndListView = CreateWindow(WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY |
		LBS_NOINTEGRALHEIGHT | LBS_EXTENDEDSEL,
		0, 0,
		iW, iH,
		_hwndParent,
		empty,
		g_hInst,
		NULL);

	ListView_SetExtendedListViewStyle(m_hWndListView,
		LVS_EX_GRIDLINES
		| LVS_EX_DOUBLEBUFFER
		| LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERINALLVIEWS
		| LVS_EX_CHECKBOXES
	);

	m_lvCol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	m_lvCol.fmt = LVCFMT_LEFT;

	InsertColumn(LV_COL_LOGTYPE, (LPWSTR)L"Log Type", iW - 17);

	for (size_t i = 0; i < 20; i++)
	{
		AddItem((LPWSTR)L"ALL");

	}
	AddItem((LPWSTR)L"ALL");
	AddItem((LPWSTR)L"bye");

	return m_hWndListView;
}

VOID LogCategoryListView::SetView(DWORD _dwView)
{
	if (!m_hWndListView) return;

	// Retrieve the current window style. 
	DWORD dwStyle = GetWindowLong(m_hWndListView, GWL_STYLE);

	// Set the window style only if the view bits changed.
	if ((dwStyle & LVS_TYPEMASK) != _dwView)
	{
		SetWindowLong(m_hWndListView,
			GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | _dwView);
	} 
}

VOID LogCategoryListView::InsertColumn(LV_COL eCol, LPWSTR _sColName, INT iWidth)
{
	if (!m_hWndListView) return;

	INT i = ListView_GetItemCount(m_hWndListView);

	m_lvCol.cx = iWidth;
	m_lvCol.pszText = _sColName;
	m_lvCol.iSubItem = eCol;
	ListView_InsertColumn(m_hWndListView, eCol, &m_lvCol);
}

VOID LogCategoryListView::AddItem(LPWSTR _sItemName)
{
	m_listItem[LV_COL_LOGTYPE].push_back(_sItemName);
	// Column 수가 늘어나면 매개변수를 더 받고 아래처럼 추가해줘야함
	// m_listItem[1].push_back(_sItemName1); 

	Notify();
}

VOID LogCategoryListView::Notify(void)
{
	if (!m_hWndListView) return;

	ListView_DeleteAllItems(m_hWndListView);

	LVITEM item;

	item.mask = LVIF_TEXT;
	item.state = 0;
	item.stateMask = 0;

	for (int i = 0; i < LV_COL_END; i++)
	{
		item.iSubItem = i;
		item.iItem = 1;
		for (LPWSTR sText : m_listItem[i])
		{
			if (item.iSubItem == 0) {
				item.pszText = sText;
				ListView_InsertItem(m_hWndListView, &item);
			}
			else {
				ListView_SetItemText(m_hWndListView, item.iItem - 1, item.iSubItem, sText);
			}
			++item.iItem;
		}
	}
}
