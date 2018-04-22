#include "stdafx.h"
#include "RenderManager.h"
#include "GraphicDevice.h"
#include "Renderer.h"
#include "Camera.h"

shared_ptr<JSRenderManager> JSRenderManager::m_pInstance = nullptr;

JSRenderManager::JSRenderManager()
{

}

JSRenderManager::~JSRenderManager()
{
	for (auto shaderSet : m_mapShader)
		delete shaderSet.second;
	m_mapShader.clear();

	for (auto buffer : m_mapVertexBuffer)
		delete buffer.second;
	m_mapVertexBuffer.clear();

	for (auto rasterizer : m_mapRasterizer)
		rasterizer.second->Release();
	m_mapRasterizer.clear();

	for (auto sampler : m_mapSampler)
		sampler.second->Release();
	m_mapSampler.clear();
}

shared_ptr<JSRenderManager> JSRenderManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		shared_ptr<JSRenderManager> instance(new JSRenderManager());
		instance->InitializeManager();
		m_pInstance = instance;
	}
	return m_pInstance;
}

void JSRenderManager::InitializeManager()
{
	CurrentShaderType = ShaderType::NONE;
	CurrentCenterType = CenterType::NONE;
	CurrentRasterizerType = RasterizerType::NONE;

	auto pd3dDevice = CGraphicDevice::GetInstance()->GetDevice();

	//Init Shader Type
	auto shaderType = ShaderType::TEXTURE_UV;
	auto shaderSet = new ShaderSet();

	D3D11_INPUT_ELEMENT_DESC d3dInputLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT nElements = ARRAYSIZE(d3dInputLayout);
	CreateVertexShaderFromFile(pd3dDevice, L"Resources/Shader/Effect.fx", "VS", "vs_4_0", &shaderSet->VertexShader, d3dInputLayout, nElements, &shaderSet->VertexLayout);
	CreatePixelShaderFromFile(pd3dDevice, L"Resources/Shader/Effect.fx", "PS", "ps_4_0", &shaderSet->PixelShader);
	m_mapShader[shaderType] = shaderSet;


	//Init Center Type - Mesh
	auto centerType = CenterType::FOOT;
	auto vertex = new VertexSet();

	Vertex vtx[6];
	vtx[0].Position = XMFLOAT3(-0.5f, 1.f, 0.f);	vtx[0].Texcoord = XMFLOAT2(0.f, 0.f);
	vtx[1].Position = XMFLOAT3(0.5f, 1.f, 0.f);		vtx[1].Texcoord = XMFLOAT2(1.f, 0.f);
	vtx[2].Position = XMFLOAT3(-0.5f, 0.f, 0.f);	vtx[2].Texcoord = XMFLOAT2(0.f, 1.f);
	vtx[3].Position = XMFLOAT3(-0.5f, 0.f, 0.f);	vtx[3].Texcoord = XMFLOAT2(0.f, 1.f);
	vtx[4].Position = XMFLOAT3(0.5f, 1.f, 0.f);		vtx[4].Texcoord = XMFLOAT2(1.f, 0.f);
	vtx[5].Position = XMFLOAT3(0.5f, 0.f, 0.f);		vtx[5].Texcoord = XMFLOAT2(1.f, 1.f);

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDesc.ByteWidth = sizeof(Vertex) * 6;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = vtx;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &vertex->VertexBuffer);
	vertex->PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	vertex->Vertices = 6;
	vertex->Stride = sizeof(Vertex);
	vertex->Offset = 0;
	m_mapVertexBuffer[centerType] = vertex;


	//Init Rasterizer Type
	auto rasterizerType = RasterizerType::SOLID_AND_CULLNONE;
	ID3D11RasterizerState* rasterizerState;

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	m_mapRasterizer[rasterizerType] = rasterizerState;


	//Init Sampler Type
	auto samplerType = SamplerType::POINT;
	ID3D11SamplerState* samplerState;

	D3D11_SAMPLER_DESC d3dSamplerDesc;
	ZeroMemory(&d3dSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	d3dSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	d3dSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	d3dSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	d3dSamplerDesc.MinLOD = 0;
	d3dSamplerDesc.MaxLOD = 0;
	pd3dDevice->CreateSamplerState(&d3dSamplerDesc, &samplerState);
	m_mapSampler[samplerType] = samplerState;

	samplerType = SamplerType::LINEAR;
	d3dSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dDevice->CreateSamplerState(&d3dSamplerDesc, &samplerState);
	m_mapSampler[samplerType] = samplerState;
}

void JSRenderManager::CreateVertexShaderFromFile(ID3D11Device * pd3dDevice, const WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11VertexShader ** ppd3dVertexShader, D3D11_INPUT_ELEMENT_DESC * pd3dInputLayout, UINT nElements, ID3D11InputLayout ** ppd3dVertexLayout)
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

void JSRenderManager::CreatePixelShaderFromFile(ID3D11Device * pd3dDevice, const WCHAR * pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderModel, ID3D11PixelShader ** ppd3dPixelShader)
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

void JSRenderManager::AddRenderer(shared_ptr<JSRenderer> renderer)
{
	auto findIter = m_mapRenderer.find(renderer->m_eRenderLayer);
	if (findIter != m_mapRenderer.end())
	{
		findIter->second.push_back(renderer);
	}
	else
	{
		m_mapRenderer[renderer->m_eRenderLayer] = list<shared_ptr<JSRenderer>>();
		m_mapRenderer[renderer->m_eRenderLayer].push_back(renderer);
	}
}

void JSRenderManager::AddCamera(shared_ptr<JSCamera> camera)
{
	m_CameraList.push_back(camera);
	m_CameraList.sort();
}

void JSRenderManager::Render()
{
	auto pd3dDeviceContext = CGraphicDevice::GetInstance()->GetDeviceContext();

	for (auto camera : m_CameraList)
	{
		camera->UpdateShaderVariables();

		for (auto rendererList : m_mapRenderer)
		{
			if (camera->HasLayer(rendererList.first) == false)
				continue;

			for (auto renderer : rendererList.second)
			{
				if (renderer->m_eShaderType != CurrentShaderType)
				{
					CurrentShaderType = renderer->m_eShaderType;
					auto shaderSet = m_mapShader[CurrentShaderType];

					pd3dDeviceContext->IASetInputLayout(shaderSet->VertexLayout);
					pd3dDeviceContext->VSSetShader(shaderSet->VertexShader, NULL, 0);
					pd3dDeviceContext->PSSetShader(shaderSet->PixelShader, NULL, 0);
				}

				if (renderer->m_eCenterType != CurrentCenterType)
				{
					CurrentCenterType = renderer->m_eCenterType;
					auto vertexSet = m_mapVertexBuffer[CurrentCenterType];
					pd3dDeviceContext->IASetVertexBuffers(0, 1, &vertexSet->VertexBuffer, &vertexSet->Stride, &vertexSet->Offset);
					pd3dDeviceContext->IASetPrimitiveTopology(vertexSet->PrimitiveTopology);
				}

				if (renderer->m_eRasterizerType != CurrentRasterizerType)
				{
					CurrentRasterizerType = renderer->m_eRasterizerType;
					pd3dDeviceContext->RSSetState(m_mapRasterizer[CurrentRasterizerType]);
				}

				if (renderer->m_eSamplerType != CurrentSamplerType)
				{
					CurrentSamplerType = renderer->m_eSamplerType;
					pd3dDeviceContext->PSSetSamplers(PS_SLOT_SAMPLER, 1, &m_mapSampler[CurrentSamplerType]);
				}

				renderer->Render();
				pd3dDeviceContext->Draw(m_mapVertexBuffer[CurrentCenterType]->Vertices, 0);
			}
		}
	}
}
