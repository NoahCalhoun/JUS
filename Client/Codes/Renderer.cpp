#include "stdafx.h"
#include "Renderer.h"
#include "GraphicDevice.h"
#include "RenderManager.h"
#include "Transform.h"

JSRenderer::JSRenderer()
	: m_eRenderLayer(RenderLayer::BACKGROUND)
	, m_eShaderType(ShaderType::TEXTURE_UV)
	, m_eCenterType(CenterType::FOOT)
	, m_eRasterizerType(RasterizerType::SOLID_AND_CULLNONE)
	, m_eSamplerType(SamplerType::POINT)
	, m_pConstantBuffer(nullptr)
	, m_pResourceView(nullptr)
	, m_pTransform(nullptr)
{
}

JSRenderer::~JSRenderer()
{
	if (m_pConstantBuffer)
		m_pConstantBuffer->Release();
	if (m_pResourceView)
		m_pResourceView->Release();
}

shared_ptr<JSRenderer> JSRenderer::Create()
{
	shared_ptr<JSRenderer> value(new JSRenderer);
	return value;
}

void JSRenderer::InitComponent()
{
	m_pTransform = m_pOwner->GetComponent<JSTransform>();

	auto pd3dDevice = CGraphicDevice::GetInstance()->GetDevice();

	D3D11_BUFFER_DESC bd;
	::ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(JSMATRIX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	pd3dDevice->CreateBuffer(&bd, NULL, &m_pConstantBuffer);

	D3DX11CreateShaderResourceViewFromFile(
		pd3dDevice,
		_T("Resources/Texture/test.bmp"),
		NULL,
		NULL,
		&m_pResourceView,
		NULL);
}

void JSRenderer::UpdateComponent()
{
}

void JSRenderer::SetLayer(RenderLayer layer)
{
	m_eRenderLayer = layer;
}

void JSRenderer::SetRenderType(ShaderType shader, CenterType center, RasterizerType rasterizer, SamplerType sampler)
{
	m_eShaderType = shader;
	m_eCenterType = center;
	m_eRasterizerType = rasterizer;
	m_eSamplerType = sampler;
}

void JSRenderer::Render()
{
	auto worldMat = m_pTransform->GetWorld();
	auto pd3dDeviceContext = CGraphicDevice::GetInstance()->GetDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	pd3dDeviceContext->Map(m_pConstantBuffer
		, 0
		, D3D11_MAP_WRITE_DISCARD
		, 0
		, &mappedResource);
	auto bufferData = (JSMATRIX*)mappedResource.pData;
	*bufferData = XMMatrixTranspose(*worldMat);
	pd3dDeviceContext->Unmap(m_pConstantBuffer, 0);

	pd3dDeviceContext->VSSetConstantBuffers(VS_SLOT_WORLD_MATRIX, 1, &m_pConstantBuffer);
	pd3dDeviceContext->PSSetShaderResources(PS_SLOT_TEXTURE, 1, &m_pResourceView);
}
