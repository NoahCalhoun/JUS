#pragma once

enum LOGTYPE {
	LOGTYPE_ALL,
	LOGTYPE_MOVE,

	LOGTYPE_COUNT,
	LOGTYPE_END = LOGTYPE_COUNT,
};

class CLogCategoryListView;
class CLogListBox;
class CLog
{
public:
	CLog();
	virtual ~CLog();

private:
	shared_ptr<CLogCategoryListView> m_pCategoryListView;
	shared_ptr<CLogListBox> m_pListBox;

	list<STRING> m_listlogs[LOGTYPE_COUNT];

public:
	void Initialize(void);
	void Notify(void);

	void AddLog(LOGTYPE _eType, STRING _str);
};