#pragma once

#include "TestMesh.h"

class CTestObject
{
public:
	CTestObject();
	virtual ~CTestObject();

public:
	D3DXMATRIX m_matWorld;
	shared_ptr<CTestMesh> m_pMesh;
	virtual void SetMesh(shared_ptr<CTestMesh> pMesh);
	virtual void Animate(float fTimeElapesd);
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);
};

class CTestTriangle : public CTestObject
{
public :
	CTestTriangle();
	virtual ~CTestTriangle();
	virtual void Animate(float fTimeElapesd);
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);
};