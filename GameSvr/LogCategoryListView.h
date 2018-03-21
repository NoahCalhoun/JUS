#pragma once

#include <CommCtrl.h>
#include "Log.h"

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
	
	list<STRING> m_listItem[LV_COL_END];
public:
	HWND CreateListView(HWND _hwndParent);
	void SetView(DWORD _dwView);

	void InsertColumn(LV_COL _eCol, STRING _sColName, INT _iWidth);
	void AddItem(LV_COL _eCol, STRING _sItemName);
	void Notify(void);

	void GetCheckedList(list<INT>& _listChecked);
	BOOL IsChecked(LOGTYPE _eType);
};