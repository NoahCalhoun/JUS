#include "stdafx.h"
#include "Camera.h"
#include "Transform.h"
#include "GraphicDevice.h"

JSCamera::JSCamera()
	: m_pTransform(nullptr)
	, m_matView(JSMATRIX::Identity())
	, m_matProject(JSMATRIX::Identity())
	, m_pVeiwProjConstBuffer(nullptr)
	, Layer(0)
{
	::ZeroMemory(&m_tViewport, sizeof(D3D11_VIEWPORT));
}

JSCamera::~JSCamera()
{
	if (m_pVeiwProjConstBuffer)
		m_pVeiwProjConstBuffer->Release();
}

shared_ptr<JSCamera> JSCamera::Create()
{
	shared_ptr<JSCamera> value(new JSCamera());
	return value;
}

void JSCamera::InitComponent()
{
	JSRenderManager::GetInstance()->AddCamera(m_pOwner->GetComponent<JSCamera>());
	m_pTransform = m_pOwner->GetComponent<JSTransform>();
}

void JSCamera::UpdateComponent()
{
	GenerateView();

	UpdateShaderVariables();
}

void JSCamera::SetViewport(DWORD _xTopLeft, DWORD _yTopLeft, DWORD _width, DWORD _height, float _minZ, float _maxZ)
{
	m_tViewport.TopLeftX = _xTopLeft;
	m_tViewport.TopLeftY = _yTopLeft;
	m_tViewport.Width = _width;
	m_tViewport.Height = _height;
	m_tViewport.MinDepth = _minZ;
	m_tViewport.MaxDepth = _maxZ;
	CGraphicDevice::GetInstance()->GetDeviceContext()->RSSetViewports(1, &m_tViewport);
}

void JSCamera::SetProjection(bool _perspective, float _near, float _far, float _aspect_width, float _fov_height)
{
	m_bPerspective = _perspective;
	m_fNear = _near;
	m_fFar = _far;
	if (m_bPerspective)
	{
		m_tPerspective.fAspectRatio = _aspect_width;
		m_tPerspective.fFOV = _fov_height;
	}
	else
	{
		m_tOrthogonal.fWidth = _aspect_width;
		m_tOrthogonal.fHeight = _fov_height;
	}

	GenerateProject();
}

void JSCamera::AddLayer(RenderLayer layer)
{
	Layer |= (INT8)layer;
}

void JSCamera::GenerateView()
{
	auto camPosition = m_pTransform->GetPosition();
	m_matView = XMMatrixLookAtLH(camPosition->v, (*camPosition) + m_pTransform->GetBasis(EBasisVectorType::Front), m_pTransform->GetBasis(EBasisVectorType::Up).v);
}

void JSCamera::GenerateProject()
{
	m_matProject = m_bPerspective ? XMMatrixPerspectiveFovLH(m_tPerspective.fFOV, m_tPerspective.fAspectRatio, m_fNear, m_fFar)
		: XMMatrixOrthographicLH(m_tOrthogonal.fWidth, m_tOrthogonal.fHeight, m_fNear, m_fFar);
}

void JSCamera::CreateShaderVariables()
{
	D3D11_BUFFER_DESC bd;
	::ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VS_CB_VIEWPROJECTION_MATRIX);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CGraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&bd, NULL, &m_pVeiwProjConstBuffer);
}

void JSCamera::UpdateShaderVariables()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CGraphicDevice::GetInstance()->GetDeviceContext()->Map(
		m_pVeiwProjConstBuffer
		, 0
		, D3D11_MAP_WRITE_DISCARD
		, 0
		, &mappedResource);
	VS_CB_VIEWPROJECTION_MATRIX* pVP = (VS_CB_VIEWPROJECTION_MATRIX*)mappedResource.pData;
	pVP->View = XMMatrixTranspose(m_matView);
	pVP->Project = XMMatrixTranspose(m_matProject);

	CGraphicDevice::GetInstance()->GetDeviceContext()->Unmap(m_pVeiwProjConstBuffer, 0);
	CGraphicDevice::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(VS_SLOT_VIEWPROJECTION_MATRIX, 1, &m_pVeiwProjConstBuffer);
}

bool JSCamera::HasLayer(RenderLayer layer)
{
	return (Layer & (INT8)layer);
}
