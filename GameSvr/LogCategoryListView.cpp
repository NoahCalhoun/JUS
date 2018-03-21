#include "stdafx.h"
#include "LogCategoryListView.h"
 

CLogCategoryListView::CLogCategoryListView()
{
}

CLogCategoryListView::~CLogCategoryListView()
{
}

HWND CLogCategoryListView::CreateListView(HWND _hwndParent)
{
	if (!_hwndParent) return NULL;

	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(_hwndParent, &rcClient);

	INT iW = (rcClient.right - rcClient.left) / 4;
	INT iH = rcClient.bottom - rcClient.top;
	// Create the list-view window in report view with label editing enabled.
	m_hWndListView = CreateWindow(WC_LISTVIEW,
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT |
		LVS_SINGLESEL,
		0, 0,
		iW, iH,
		_hwndParent,
		HMENU(),
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

	INT iWidthWithoutScrollBarSize = iW - 17;

	InsertColumn(LV_COL_LOGTYPE, _T( "Log Type" ), iWidthWithoutScrollBarSize);

	AddItem(LV_COL_LOGTYPE, _T("ALL"));
	AddItem(LV_COL_LOGTYPE, _T("bye"));

	Notify();

	ListView_SetCheckState(m_hWndListView, 0, TRUE);

	return m_hWndListView;
}

void CLogCategoryListView::SetView(DWORD _dwView)
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

void CLogCategoryListView::InsertColumn(LV_COL _eCol, STRING _sColName, INT _iWidth)
{
	if (!m_hWndListView) return;

	INT i = ListView_GetItemCount(m_hWndListView);

	m_lvCol.cx = _iWidth;
	m_lvCol.pszText = const_cast<LPWSTR>(_sColName.c_str());;
	m_lvCol.iSubItem = _eCol;
	ListView_InsertColumn(m_hWndListView, _eCol, &m_lvCol);
}

void CLogCategoryListView::AddItem(LV_COL _eCol, STRING _sItemName)
{
	m_listItem[_eCol].push_back(_sItemName);
}

void CLogCategoryListView::Notify(void)
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
		for (auto sText : m_listItem[i])
		{
			LPWSTR sItemText = const_cast<LPWSTR>(sText.c_str());
			if (item.iSubItem == 0) {
				item.pszText = sItemText;
				ListView_InsertItem(m_hWndListView, &item);
			}
			else {
				ListView_SetItemText(m_hWndListView, item.iItem - 1, item.iSubItem, sItemText);
			}
			++item.iItem;
		}
	}
}

void CLogCategoryListView::GetCheckedList(list<INT>& _listChecked)
{
	for (INT i = 0; i < LV_COL_END; i++)
	{
		if (ListView_GetCheckState(m_hWndListView, i)) 
			_listChecked.push_back(i);
	}
}

BOOL CLogCategoryListView::IsChecked(LOGTYPE _eType)
{
	return ListView_GetCheckState(m_hWndListView, _eType);
}