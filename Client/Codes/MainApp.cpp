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
}

void CMainApp::UpdateApplication()
{
	m_pInputDev->UpdateDevice();
	m_pGraphicDev->UpdateDevice();
}

void CMainApp::ReleaseApplication()
{
	m_pGraphicDev->ReleaseDevice();
}
