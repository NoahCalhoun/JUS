#pragma once

#include <CommCtrl.h>

class LogCategoryListView
{
public:
	enum LV_COL {
		LV_COL_LOGTYPE,

		LV_COL_END,
	};

public:
	LogCategoryListView();
	~LogCategoryListView();

protected:
	HWND m_hWndListView;
	LVCOLUMN m_lvCol;

	list<LPWSTR> m_listItem[LV_COL_END];

public:
	HWND CreateListView(HWND _hwndParent);
	VOID SetView(DWORD _dwView);

	VOID InsertColumn(LV_COL eCol, LPWSTR _sColName, INT iWidth);
	VOID AddItem(LPWSTR _sItemName);
	VOID Notify(void);
};