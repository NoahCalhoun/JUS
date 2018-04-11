#pragma once

#include <CommCtrl.h>

class CLogCategoryListView
{
public:
	enum LV_COL {
		LV_COL_LOGTYPE,

		LV_COL_END,
	};

public:
	CLogCategoryListView();
	~CLogCategoryListView();

protected:
	HWND m_hWndListView;
	LVCOLUMN m_lvCol;

public:
	HWND CreateListView(HWND _hwndParent);
	void SetView(DWORD _dwView);

	void InsertColumn(LV_COL eCol, LPWSTR _sColName, INT iWidth);
	void AddItem(LPWSTR _sItemName);
	void Notify(void);
};