#include "stdafx.h"
#include "LogCategoryListView.h"
 

CLogCategoryListView::CLogCategoryListView()
	: m_bIgnoreRewrite(FALSE)
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

	InsertColumn(LV_COL_LOGTYPE, _T("Log Type"), iWidthWithoutScrollBarSize);

	ColumnRegister();

	SetCheck(LOGTYPE_ALL, TRUE);

	return m_hWndListView;
}

BOOL CLogCategoryListView::OnNotify(LPNMLISTVIEW pNMLV)
{
	BOOL bRewrite = FALSE;

	switch (pNMLV->hdr.code)
	{
	case LVN_ITEMCHANGED:
	{
		if (pNMLV->uChanged & LVIF_STATE) /* Item state has been changed */
		{
			switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
			{
			case 0x2000: /* CHECKED */
			{
				synchronized(m_lock) m_aChecked[pNMLV->iItem] = TRUE;

				if (pNMLV->iItem == LOGTYPE_ALL) {
					for (int i = 1; i < LOGTYPE_COUNT; i++)
					{
						SetCheck((LOGTYPE)i, FALSE);
					}
				}
				else {
					SetCheck(LOGTYPE_ALL, FALSE);
				}
				if (!m_bIgnoreRewrite) bRewrite = TRUE;
			}
			break;

			case 0x1000: /* UNCHECKED */
			{
				synchronized(m_lock) m_aChecked[pNMLV->iItem] = FALSE;
				if (!m_bIgnoreRewrite) bRewrite = TRUE;
			}
			break;
			}
		}
	}
	break;
	}

	return bRewrite;
}

BOOL CLogCategoryListView::IsChecked(LOGTYPE _eType)
{
	auto_lock(m_lock);
	return m_aChecked[_eType];
}

void CLogCategoryListView::SetCheck(LOGTYPE _eType, BOOL _bCheck)
{
	m_bIgnoreRewrite = TRUE;
	ListView_SetCheckState(m_hWndListView, _eType, _bCheck);
	m_bIgnoreRewrite = FALSE;
	synchronized(m_lock) m_aChecked[_eType] = _bCheck;
}

INT CLogCategoryListView::GetCheckCount(void)
{
	INT iCnt = 0;
	for (INT i = 0; i < LOGTYPE_COUNT; i++)
	{
		if (IsChecked((LOGTYPE)i))
			++iCnt;
	}

	return iCnt;
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

void CLogCategoryListView::ColumnRegister(void)
{
	if (!m_hWndListView) return;

	vector<STRING> aItem[LV_COL_END];

	STRING sTypeName[LOGTYPE_COUNT] = {
		_T("ALL"),
		_T("0"),
		_T("1"),
		/*
		_T("2"),
		_T("3"),
		_T("4"),
		_T("5"),
		_T("6"),
		_T("7"),
		_T("8"),
		_T("9"),
		_T("10"),
		_T("11"),
		_T("12"),
		_T("13"),
		_T("14"),
		_T("15"),
		*/
	};

	aItem[LV_COL_LOGTYPE].resize(LOGTYPE_COUNT);
	m_aChecked.resize(LOGTYPE_COUNT, FALSE);
	for (INT i = 0; i < LOGTYPE_COUNT; i++)
	{
		aItem[LV_COL_LOGTYPE][i] = sTypeName[i];
	}

	LVITEM item;

	item.mask = LVIF_TEXT;
	item.state = 0;
	item.stateMask = 0;

	for (int i = 0; i < LV_COL_END; i++)
	{
		item.iSubItem = i;
		item.iItem = 1;
		for (auto sText : aItem[i])
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