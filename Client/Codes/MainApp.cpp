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

	m_pScene = make_shared<CTestScene>();
	m_pScene->BuildObjects(m_pGraphicDev->GetDevice());
}

void CMainApp::UpdateApplication()
{
	m_pTimeMgr->Tick(60);

	m_pInputDev->UpdateDevice();
	//m_pGraphicDev->UpdateDevice();

	float fClearColor[4] = { 0.f, 0.125f, 0.3f, 1.f };
	m_pGraphicDev->GetDeviceContext()->ClearRenderTargetView(m_pGraphicDev->GetRenderTargetView(), fClearColor);

	m_pScene->Render(m_pGraphicDev->GetDeviceContext());

	m_pGraphicDev->GetSwapChain()->Present(0, 0);

	m_pTimeMgr->GetFrameRate(m_pszBuffer, 10);
	SetWindowText(g_hWnd, m_pszBuffer);
}

void CMainApp::ReleaseApplication()
{
	m_pScene->ReleaseObjects();
	m_pGraphicDev->ReleaseDevice();
}
