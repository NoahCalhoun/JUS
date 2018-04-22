#include "stdafx.h"
#include "GraphicDevice.h"

shared_ptr<CGraphicDevice> CGraphicDevice::m_pInstance = nullptr;

CGraphicDevice::CGraphicDevice()
{
	m_pd3dDevice = NULL;
	m_pDXGISwapChain = NULL;
	m_pd3dDeviceContext = NULL;
	m_pd3dRenderTargetView = NULL;

	m_iClientWindowWidth = CLIENT_WINDOW_WIDTH;
	m_iClientWindowHeight = CLIENT_WINDOW_HEIGHT;
}

CGraphicDevice::~CGraphicDevice()
{
	ReleaseDevice();
}

shared_ptr<CGraphicDevice> CGraphicDevice::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = make_shared<CGraphicDevice>();
	}

	return m_pInstance;
}

HRESULT CGraphicDevice::InitGraphicDevice()
{
	HRESULT hr;

	RECT rc;
	::GetClientRect(g_hWnd, &rc);
	m_iClientWindowWidth = rc.right - rc.left;
	m_iClientWindowHeight = rc.bottom - rc.top;

	UINT dwCreateDeviceFlags = 0;
#ifdef _DEBUG
	dwCreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE d3dDriverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT nDriverTypes = sizeof(d3dDriverTypes) / sizeof(D3D_DRIVER_TYPE);
	D3D_FEATURE_LEVEL pd3dFeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	UINT nFeatureLevels = sizeof(pd3dFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);

	DXGI_SWAP_CHAIN_DESC dxgiSwapChainDesc;
	::ZeroMemory(&dxgiSwapChainDesc, sizeof(dxgiSwapChainDesc));
	dxgiSwapChainDesc.BufferCount = 1;
	dxgiSwapChainDesc.BufferDesc.Width = m_iClientWindowWidth;
	dxgiSwapChainDesc.BufferDesc.Height = m_iClientWindowHeight;
	dxgiSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	dxgiSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	dxgiSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainDesc.OutputWindow = g_hWnd;
	dxgiSwapChainDesc.SampleDesc.Count = 1;
	dxgiSwapChainDesc.SampleDesc.Quality = 0;
	dxgiSwapChainDesc.Windowed = true;

	D3D_DRIVER_TYPE nd3dDriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL nd3dFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	
	for (UINT i = 0; i < nDriverTypes; ++i)
	{
		nd3dDriverType = d3dDriverTypes[i];
		
		if (SUCCEEDED(hr = D3D11CreateDeviceAndSwapChain(
				NULL,
				nd3dDriverType,
				NULL,
				dwCreateDeviceFlags,
				pd3dFeatureLevels,
				nFeatureLevels,
				D3D11_SDK_VERSION,
				&dxgiSwapChainDesc,
				&m_pDXGISwapChain,
				&m_pd3dDevice,
				&nd3dFeatureLevel,
				&m_pd3dDeviceContext
			)))
		{
			break;
		}
	}

	if (!m_pDXGISwapChain || !m_pd3dDevice || !m_pd3dDeviceContext)
		return E_FAIL;

	if (!CreateRenderTargetView())
		return E_FAIL;

	SetViewport();

	return S_OK;
}

void CGraphicDevice::UpdateDevice()
{
	float fClearColor[4] = { 0.f, 0.125f, 0.3f, 1.f };
	m_pd3dDeviceContext->ClearRenderTargetView(m_pd3dRenderTargetView, fClearColor);
	m_pDXGISwapChain->Present(0, 0);
}

void CGraphicDevice::RenewDeviceSize(int _width, int _height)
{
	m_iClientWindowWidth = _width;
	m_iClientWindowHeight = _height;

	m_pd3dDeviceContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pd3dRenderTargetView)
		m_pd3dRenderTargetView->Release();
	m_pDXGISwapChain->ResizeBuffers(2, m_iClientWindowWidth, m_iClientWindowHeight, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

	ID3D11Texture2D* pd3dBackBuffer;

	m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pd3dBackBuffer);
	m_pd3dDevice->CreateRenderTargetView(pd3dBackBuffer, NULL, &m_pd3dRenderTargetView);

	if (pd3dBackBuffer)
		pd3dBackBuffer->Release();

	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_pd3dRenderTargetView, NULL);
}

void CGraphicDevice::SetViewport()
{
	D3D11_VIEWPORT d3dViewport;
	d3dViewport.TopLeftX = 0.f;
	d3dViewport.TopLeftY = 0.f;
	d3dViewport.Width = (float)m_iClientWindowWidth;
	d3dViewport.Height = (float)m_iClientWindowHeight;
	d3dViewport.MinDepth = 0.f;
	d3dViewport.MaxDepth = 1.f;
	m_pd3dDeviceContext->RSSetViewports(1, &d3dViewport);
}

bool CGraphicDevice::CreateRenderTargetView()
{
	HRESULT hr;
	ID3D11Texture2D* pd3dBackBuffer;

	if (FAILED(hr = m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pd3dBackBuffer)))
		return false;

	if (FAILED(hr = m_pd3dDevice->CreateRenderTargetView(pd3dBackBuffer, NULL, &m_pd3dRenderTargetView)))
		return false;

	if (pd3dBackBuffer)
		pd3dBackBuffer->Release();

	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_pd3dRenderTargetView, NULL);

	return true;
}

void CGraphicDevice::ReleaseDevice()
{
	if (m_pd3dDeviceContext)
		m_pd3dDeviceContext->ClearState();
	if (m_pd3dRenderTargetView)
		m_pd3dRenderTargetView->Release();
	if (m_pDXGISwapChain)
		m_pDXGISwapChain->Release();
	if (m_pd3dDeviceContext)
		m_pd3dDeviceContext->Release();
	if (m_pd3dDevice)
		m_pd3dDevice->Release();
}
