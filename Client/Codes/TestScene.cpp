#include "stdafx.h"
#include "TestScene.h"

#include "GraphicDevice.h"

CTestScene::CTestScene()
	: m_ppShaders(NULL), m_ppObjects(NULL)
{
	m_nShaders = 0;
	m_nObjects = 0;
}

CTestScene::~CTestScene()
{
}

void CTestScene::BuildObjects(ID3D11Device * pd3dDevice)
{
	m_nShaders = 1;
	m_ppShaders = new shared_ptr<CObjectShader>[m_nShaders];
	m_ppShaders[0] = make_shared<CObjectShader>();
	m_ppShaders[0]->CreateShader(CGraphicDevice::GetInstance()->GetDevice(), 1);
	m_nObjects = 1;
	m_ppObjects = new shared_ptr<CTestTriangle>[m_nObjects];
	m_ppObjects[0] = make_shared<CTestTriangle>();
	m_ppObjects[0]->SetMesh(make_shared<CTriangleMesh>(CGraphicDevice::GetInstance()->GetDevice()));

	m_ppShaders[0]->AddObject(m_ppObjects[0]);
}

void CTestScene::ReleaseObjects()
{
	delete[] m_ppShaders;
	delete[] m_ppObjects;
}

void CTestScene::AnimateObjects(float fTimeElapsed)
{
}

void CTestScene::Render(ID3D11DeviceContext * pd3dDeviceContext)
{
	for (int i = 0; i < m_nShaders; ++i)
	{
		m_ppShaders[i]->Render(CGraphicDevice::GetInstance()->GetDeviceContext());
	}
}
