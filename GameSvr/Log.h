#pragma once

#include <CommCtrl.h>

enum LOGTYPE {
	LOGTYPE_ALL,
	LOGTYPE_0,
	LOGTYPE_1,
	/*
	LOGTYPE_2,
	LOGTYPE_3,
	LOGTYPE_4,
	LOGTYPE_5,
	LOGTYPE_6,
	LOGTYPE_7,
	LOGTYPE_8,
	LOGTYPE_9,
	LOGTYPE_10,
	LOGTYPE_11,
	LOGTYPE_12,
	LOGTYPE_13,
	LOGTYPE_14,
	LOGTYPE_15,
	*/

	LOGTYPE_COUNT,
	LOGTYPE_END = LOGTYPE_COUNT,
};

class CLogCategoryListView;
class CLogListBox;
class CLog
{
private:
	struct LOG_INFO
	{
		LOGTYPE eType;
		STRING sLog;
	};

public:
	CLog();
	virtual ~CLog();

private:
	HWND m_hListView;
	HWND m_hListBox;

	shared_ptr<CLogCategoryListView> m_pCategoryListView;
	shared_ptr<CLogListBox> m_pListBox;

	LOCK m_lock;
	list<LOG_INFO> m_listLogs;
	list<LOG_INFO> m_listNewLogs;

public:
	void Initialize(void);
	void OnNotifyListView(LPNMLISTVIEW pNMLV);

	void AddLog(LOGTYPE _eType, STRING _str);
	void UpdateLog(void);

	HWND GetListViewHandle(void);
	HWND GetListBoxHandle(void);

private:
	void AddString(LOGTYPE _eType, const STRING& _str);
	void Rewrite(void);
};