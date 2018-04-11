#include "stdafx.h"
#include "TestMesh.h"

CTestMesh::CTestMesh(ID3D11Device* pd3dDevice)
{
	m_nStride = sizeof(CVertex);
	m_nOffset = 0;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

CTestMesh::~CTestMesh()
{
	if (m_pd3dVertexBuffer)
		m_pd3dVertexBuffer->Release();
}

void CTestMesh::Render(ID3D11DeviceContext* pd3dDeviceContext)
{
	if (m_pd3dVertexBuffer)
		pd3dDeviceContext->IASetVertexBuffers(0, 1, &m_pd3dVertexBuffer, &m_nStride, &m_nOffset);
	pd3dDeviceContext->IASetPrimitiveTopology(m_d3dPrimitiveTopology);
	pd3dDeviceContext->Draw(m_nVertices, m_nOffset);
}

CTriangleMesh::CTriangleMesh(ID3D11Device* pd3dDevice)
	: CTestMesh(pd3dDevice)
{
	CVertex pVertices[3];
	pVertices[0] = CVertex(0.f, 0.5f, 0.f);
	pVertices[1] = CVertex(0.5f, -0.5f, 0.f);
	pVertices[2] = CVertex(-0.5f, -0.5f, 0.f);

	D3D11_BUFFER_DESC d3dBufferDesc;
	ZeroMemory(&d3dBufferDesc, sizeof(D3D11_BUFFER_DESC));
	d3dBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3dBufferDesc.ByteWidth = sizeof(CVertex) * 3;
	d3dBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	d3dBufferDesc.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA d3dBufferData;
	ZeroMemory(&d3dBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	d3dBufferData.pSysMem = pVertices;
	pd3dDevice->CreateBuffer(&d3dBufferDesc, &d3dBufferData, &m_pd3dVertexBuffer);

	m_nVertices = 3;
	m_nStride = sizeof(CVertex);
	m_nOffset = 0;
	m_d3dPrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

CTriangleMesh::~CTriangleMesh()
{
}

void CTriangleMesh::Render(ID3D11DeviceContext* pd3dDeviceContext)
{
	CTestMesh::Render(pd3dDeviceContext);
}
