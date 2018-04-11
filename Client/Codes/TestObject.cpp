#include "stdafx.h"
#include "TestObject.h"

CTestObject::CTestObject()
{
}

CTestObject::~CTestObject()
{
}

void CTestObject::SetMesh(shared_ptr<CTestMesh> pMesh)
{
	m_pMesh = pMesh;
}

void CTestObject::Animate(float fTimeElapesd)
{
}

void CTestObject::Render(ID3D11DeviceContext * pd3dDeviceContext)
{
	if (m_pMesh)
		m_pMesh->Render(pd3dDeviceContext);
}

CTestTriangle::CTestTriangle()
{
}

CTestTriangle::~CTestTriangle()
{
}

void CTestTriangle::Animate(float fTimeElapesd)
{
	CTestObject::Animate(fTimeElapesd);
}

void CTestTriangle::Render(ID3D11DeviceContext * pd3dDeviceContext)
{
	CTestObject::Render(pd3dDeviceContext);
}
