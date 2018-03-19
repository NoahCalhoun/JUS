#pragma once

#include "TestObject.h"
#include "TestShader.h"

class CTestScene
{
public:
	CTestScene();
	~CTestScene();

private:
	shared_ptr<CObjectShader>* m_ppShaders;
	int m_nShaders;
	shared_ptr<CTestTriangle>* m_ppObjects;
	int m_nObjects;
	
public:
	void BuildObjects(ID3D11Device* pd3dDevice);
	void ReleaseObjects();
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D11DeviceContext* pd3dDeviceContext);
};