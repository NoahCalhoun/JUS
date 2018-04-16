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
	
	LOCK m_lock;
	vector<BOOL> m_aChecked;
public:
	HWND CreateListView(HWND _hwndParent);

	BOOL OnNotify(LPNMLISTVIEW pNMLV);

	BOOL IsChecked(LOGTYPE _eType);
	void SetCheck(LOGTYPE _eType, BOOL _bCheck);
	INT GetCheckCount(void);

private:
	void InsertColumn(LV_COL _eCol, STRING _sColName, INT _iWidth);
	void ColumnRegister(void);

};