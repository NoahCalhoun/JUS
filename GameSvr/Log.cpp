#include "stdafx.h"
#include "Log.h"

#include "LogCategoryListView.h"
#include "LogListBox.h"

CLog::CLog()
	: m_pCategoryListView(NULL)
{
}

CLog::~CLog()
{
}

void CLog::Initialize(void)
{
	m_pCategoryListView = make_shared<CLogCategoryListView>();
	if (g_hWnd && m_pCategoryListView)	
		m_hListView = m_pCategoryListView->CreateListView(g_hWnd);

	m_pListBox = make_shared<CLogListBox>();
	if (g_hWnd && m_pListBox) 
		m_hListBox = m_pListBox->CreateListBox(g_hWnd);
}

void CLog::OnNotifyListView(LPNMLISTVIEW pNMLV)
{
	if (m_pCategoryListView && m_pCategoryListView->OnNotify(pNMLV))
		Rewrite();
}

void CLog::AddLog(LOGTYPE _eType, STRING _str)
{
	if (_eType < 0 || _eType >= LOGTYPE_COUNT) return;

	auto_lock(m_lock);

	if (m_listNewLogs.size() >= LOG_COUNT_MAX) m_listNewLogs.pop_front();
	m_listNewLogs.push_back({ _eType, _str });
}

void CLog::UpdateLog(void)
{
	auto_lock(m_lock);
	if (!m_pListBox || !m_pCategoryListView) return;

	for (auto log : m_listNewLogs)
	{
		AddString(log.eType, log.sLog);
	}
	
	m_listLogs.splice(m_listLogs.end(), m_listNewLogs);

	AntiFlood();
}

HWND CLog::GetListViewHandle(void)
{
	return m_hListView;
}

HWND CLog::GetListBoxHandle(void)
{
	return m_hListBox;
}

void CLog::AddString(LOGTYPE _eType, const STRING & _str)
{
	if (!m_pListBox || !m_pCategoryListView) return;

	if (m_pCategoryListView->IsChecked(LOGTYPE_ALL)) m_pListBox->AddString(_str);
	else if (m_pCategoryListView->IsChecked(_eType)) m_pListBox->AddString(_str);
}

void CLog::AntiFlood(void)
{
	while (m_listLogs.size() > LOG_COUNT_MAX) {
		m_listLogs.pop_front();
	}
}

void CLog::Rewrite(void)
{
	if (!m_pListBox || !m_pCategoryListView) return;

	m_pListBox->Clear();
	m_pListBox->Reserve();

	synchronized(m_lock) 
	{
		AntiFlood();

		for (auto log : m_listLogs)
		{
			AddString(log.eType, log.sLog);
		}
	}
}