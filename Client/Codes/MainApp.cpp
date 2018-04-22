#include "stdafx.h"
#include "MainApp.h"

#include "GraphicDevice.h"
#include "InputDevice.h"
#include "TimeManager.h"
#include "RenderManager.h"

#include "JSObjectBase.hpp"
#include "Transform.h"
#include "Camera.h"
#include "Renderer.h"

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

	m_pRenderManager = JSRenderManager::GetInstance();

	m_pCamera = JSObjectBase::Create();
	auto transform = m_pCamera->AddComponent<JSTransform>();
	JSVECTOR pos(0, 0, -10);
	transform->SetPosition(pos);
	/*JSVECTOR rot(0, 0, XMConvertToRadians(60));
	transform->SetRotation(rot);*/
	auto camera = m_pCamera->AddComponent<JSCamera>();
	//camera->SetProjection(true, 1, 100, (float)CLIENT_WINDOW_WIDTH / (float)CLIENT_WINDOW_HEIGHT, D3DXToRadian(60));
	camera->SetProjection(false, 0, 20, 4, 3);
	camera->CreateShaderVariables();
	camera->AddLayer(RenderLayer::CHARACTER);

	m_pObject = JSObjectBase::Create();
	auto trans = m_pObject->AddComponent<JSTransform>();
	auto renderer = m_pObject->AddComponent<JSRenderer>();
	renderer->SetLayer(RenderLayer::CHARACTER);
	renderer->SetRenderType(ShaderType::TEXTURE_UV, CenterType::FOOT, RasterizerType::SOLID_AND_CULLNONE, SamplerType::LINEAR);
	JSRenderManager::GetInstance()->AddRenderer(renderer);
}

void CMainApp::UpdateApplication()
{
	m_pTimeMgr->Tick(60);

	m_pInputDev->UpdateDevice();

	float fClearColor[4] = { 0.f, 0.125f, 0.3f, 1.f };
	m_pGraphicDev->GetDeviceContext()->ClearRenderTargetView(m_pGraphicDev->GetRenderTargetView(), fClearColor);

	m_pObject->Update();
	m_pCamera->Update();

	m_pRenderManager->GetInstance()->Render();

	m_pGraphicDev->GetSwapChain()->Present(0, 0);

	m_pTimeMgr->GetFrameRate(m_pszBuffer, 10);
	SetWindowText(g_hWnd, m_pszBuffer);
}

void CMainApp::ReleaseApplication()
{
	//m_pGraphicDev->ReleaseDevice();
}
