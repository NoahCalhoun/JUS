#pragma once

class CVertex
{
	D3DXVECTOR3 m_vPosition;

public:
	CVertex() { m_vPosition = D3DXVECTOR3(0, 0, 0); }
	CVertex(D3DXVECTOR3 position) { m_vPosition = position; }
	CVertex(float _x, float _y, float _z) { m_vPosition = D3DXVECTOR3(_x, _y, _z); }
	~CVertex() { }
};

class CTestMesh
{
public:
	CTestMesh(ID3D11Device* pd3dDevice);
	virtual ~CTestMesh();

protected:
	ID3D11Buffer* m_pd3dVertexBuffer;
	UINT m_nVertices;
	UINT m_nStride;
	UINT m_nOffset;
	D3D11_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology;

public:
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);
};

class CTriangleMesh : public CTestMesh
{
public:
	CTriangleMesh(ID3D11Device* pd3dDevice);
	virtual ~CTriangleMesh();
	virtual void Render(ID3D11DeviceContext* pd3dDeviceContext);
};