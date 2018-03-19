#pragma once

#include "TestObject.h"

class CTestShader
{
public:
	CTestShader();
	virtual ~CTestShader();

	void CreateVertexShaderFromFile(ID3D11Device* pd3dDevice
		, const WCHAR* pszFileName
		, LPCSTR pszShaderName
		, LPCSTR pszShaderModel
		, ID3D11VertexShader** ppd3dVertexShader
		, D3D11_INPUT_ELEMENT_DESC* pd3dInputLayout
		, UINT nElements
		, ID3D11InputLayout** ppd3dVertexLayout);

	void CreatePixelShaderFromFile(ID3D11Device* pd3dDevice
		, const WCHAR* pszFileName
		, LPCSTR pszShaderName
		, LPCSTR pszShaderModel
		, ID3D11PixelShader** ppd3dPixelShader);

	virtual void CreateShader(ID3D11Device* pd3dDevice);
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);

public:
	ID3D11VertexShader* m_pd3dVertexShader;
	ID3D11InputLayout* m_pd3dVertexLayout;
	ID3D11PixelShader* m_pd3dPixelShader;
};

class CObjectShader : public CTestShader
{
public:
	CObjectShader();
	virtual ~CObjectShader();
	virtual void CreateShader(ID3D11Device* pd3dDevice, int nObjects);
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);

private:
	shared_ptr<CTestObject>* m_ppObject;
	int m_nObjects;
	int m_nIndexToAdd;

public:
	void AddObject(shared_ptr<CTestObject> pObject);
};