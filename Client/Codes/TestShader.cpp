#include "stdafx.h"
#include "TestShader.h"

CTestShader::CTestShader()
{
	m_pd3dVertexShader = NULL;
	m_pd3dVertexLayout = NULL;
	m_pd3dPixelShader = NULL;
}

CTestShader::~CTestShader()
{
	if (m_pd3dVertexShader)
		m_pd3dVertexShader->Release();
	if (m_pd3dVertexLayout)
		m_pd3dVertexLayout->Release();
	if (m_pd3dPixelShader)
		m_pd3dPixelShader->Release();
}

void CTestShader::CreateVertexShaderFromFile(ID3D11Device * pd3dDevice, const WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11VertexShader ** ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC * pd3dInputLayout, UINT nElements, ID3D11InputLayout ** ppd3dVertexLayout)
{
	HRESULT hr;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pd3dShaderBlob = NULL, *pd3dErrorBlob = NULL;

	if (SUCCEEDED(hr = D3DX11CompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderModel, dwShaderFlags, 0, NULL
		, &pd3dShaderBlob, &pd3dErrorBlob, NULL)))
	{
		pd3dDevice->CreateVertexShader(pd3dShaderBlob->GetBufferPointer(), pd3dShaderBlob->GetBufferSize(), NULL, ppd3dVertexShader);
		pd3dDevice->CreateInputLayout(pd3dInputLayout, nElements, pd3dShaderBlob->GetBufferPointer(), pd3dShaderBlob->GetBufferSize(), ppd3dVertexLayout);
		pd3dShaderBlob->Release();
	}
}

void CTestShader::CreatePixelShaderFromFile(ID3D11Device * pd3dDevice, const WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader ** ppd3dPixelShader)
{
	HRESULT hr;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pd3dShaderBlob = NULL, *pd3dErrorBlob = NULL;

	if (SUCCEEDED(hr = D3DX11CompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderModel, dwShaderFlags, 0, NULL
		, &pd3dShaderBlob, &pd3dErrorBlob, NULL)))
	{
		pd3dDevice->CreatePixelShader(pd3dShaderBlob->GetBufferPointer(), pd3dShaderBlob->GetBufferSize(), NULL, ppd3dPixelShader);
		pd3dShaderBlob->Release();
	}
}

void CTestShader::CreateShader(ID3D11Device * pd3dDevice)
{
}

void CTestShader::Render(ID3D11DeviceContext * pd3dDeviceContext)
{
	if (m_pd3dVertexLayout)
		pd3dDeviceContext->IASetInputLayout(m_pd3dVertexLayout);
	if (m_pd3dVertexShader)
		pd3dDeviceContext->VSSetShader(m_pd3dVertexShader, NULL, 0);
	if (m_pd3dPixelShader)
		pd3dDeviceContext->PSSetShader(m_pd3dPixelShader, NULL, 0);
}

CObjectShader::CObjectShader()
{
	m_ppObject = NULL;
	m_nObjects = 0;
	m_nIndexToAdd = 0;
}

CObjectShader::~CObjectShader()
{
	delete[] m_ppObject;
}

void CObjectShader::CreateShader(ID3D11Device * pd3dDevice, int nObjects)
{
	D3D11_INPUT_ELEMENT_DESC d3dInputLayout[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT nElements = ARRAYSIZE(d3dInputLayout);
	CreateVertexShaderFromFile(pd3dDevice, L"Resources/Shader/Effect.fx", "VS", "vs_4_0", &m_pd3dVertexShader, d3dInputLayout, nElements, &m_pd3dVertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Resources/Shader/Effect.fx", "PS", "ps_4_0", &m_pd3dPixelShader);

	m_nObjects = nObjects;
	if (m_nObjects > 0)
	{
		m_ppObject = new shared_ptr<CTestObject>[m_nObjects];
		for (int i = 0; i < m_nObjects; ++i)
			m_ppObject[i] = NULL;
	}
}

void CObjectShader::Render(ID3D11DeviceContext * pd3dDeviceContext)
{
	CTestShader::Render(pd3dDeviceContext);
	for (int i = 0; i < m_nObjects; ++i)
	{
		if (m_ppObject[i])
			m_ppObject[i]->Render(pd3dDeviceContext);
	}
}

void CObjectShader::AddObject(shared_ptr<CTestObject> pObject)
{
	if (m_ppObject)
		m_ppObject[m_nIndexToAdd++] = pObject;
}
