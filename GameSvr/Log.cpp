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
	if (g_hWnd && m_pCategoryListView)	m_pCategoryListView->CreateListView(g_hWnd);

	m_pListBox = make_shared<CLogListBox>();
	if (g_hWnd && m_pListBox)	m_pListBox->CreateListBox(g_hWnd);
}

void CLog::Notify(void)
{
	m_pListBox->Clear();

	list<INT> listChecked;
	m_pCategoryListView->GetCheckedList(listChecked);

	for (auto i : listChecked)
	{
		m_listlogs[i];
	}
}

void CLog::AddLog(LOGTYPE _eType, STRING _str)
{
	if (_eType < 0 || _eType >= LOGTYPE_COUNT) return;

	m_listlogs[_eType].push_back(_str);

	if (m_pListBox && m_pCategoryListView && m_pCategoryListView->IsChecked(_eType))
		m_pListBox->AddString(_str);
}
