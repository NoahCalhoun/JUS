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

void CLog::AddLog(wstring _str)
{
	if (m_pListBox) m_pListBox->AddString(_str);
}
