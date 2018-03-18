#include "stdafx.h"
#include "MainApp.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

void CMainApp::InitDevice()
{
	m_pGraphicDev = CGraphicDevice::GetInstance();
	m_pGraphicDev->InitGraphicDevice();

	m_pInputDev = CInputDevice::GetInstance();

	m_pTimeMgr = CTimeManager::GetInstance();
}

void CMainApp::UpdateApplication()
{
	m_pTimeMgr->Tick();

	m_pInputDev->UpdateDevice();
	m_pGraphicDev->UpdateDevice();

	m_pTimeMgr->GetFrameRate(m_pszBuffer, 10);
	SetWindowText(g_hWnd, m_pszBuffer);
}

void CMainApp::ReleaseApplication()
{
	m_pGraphicDev->ReleaseDevice();
}
