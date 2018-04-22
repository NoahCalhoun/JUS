#pragma once

#include "Define.h"

enum class RenderLayer : INT8
{
	BACKGROUND = 0x00000001,
	CHARACTER = 0x00000002,
	EFFECT = 0x00000004,
	UI = 0x00000008,
	DEBUG = 0x00000010,
};

enum class ShaderType : INT8
{
	NONE = -1,
	TEXTURE_UV,
};

enum class CenterType : INT8
{
	NONE = -1,
	FOOT,
	BODY
};

enum class RasterizerType : INT8
{
	NONE = -1,
	SOLID_AND_CULLNONE
};

enum class SamplerType : INT8
{
	NONE = -1,
	POINT,
	LINEAR,
};

struct Vertex
{
	XMFLOAT3 Position;
	XMFLOAT2 Texcoord;

	Vertex() : Position(0, 0, 0), Texcoord(0, 0) {}
	~Vertex() {}
};

class JSRenderer;
class JSCamera;

struct ShaderSet
{
	ID3D11VertexShader* VertexShader;
	ID3D11InputLayout* VertexLayout;
	ID3D11PixelShader* PixelShader;

	ShaderSet() : VertexShader(nullptr), VertexLayout(nullptr), PixelShader(nullptr) {}
	~ShaderSet()
	{
		if (VertexShader)	VertexShader->Release();
		if (VertexLayout)	VertexLayout->Release();
		if (PixelShader)	PixelShader->Release();
	}
};

struct VertexSet
{
	ID3D11Buffer* VertexBuffer;
	UINT Vertices;
	UINT Stride;
	UINT Offset;
	D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;

	VertexSet() : VertexBuffer(nullptr), Vertices(6), Stride(sizeof(Vertex)), Offset(0)
		, PrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) {}
	~VertexSet() { if (VertexBuffer)	VertexBuffer->Release(); }
};

class JSRenderManager
{
private:
	explicit JSRenderManager();
public:
	virtual ~JSRenderManager();

private:
	static shared_ptr<JSRenderManager> m_pInstance;
public:
	static shared_ptr<JSRenderManager> GetInstance();

private:
	void InitializeManager();

	void CreateVertexShaderFromFile(ID3D11Device * pd3dDevice
		,const WCHAR* pszFileName
		, LPCSTR pszShaderName
		, LPCSTR pszShaderModel
		, ID3D11VertexShader** ppd3dVertexShader
		, D3D11_INPUT_ELEMENT_DESC* pd3dInputLayout
		, UINT nElements
		, ID3D11InputLayout** ppd3dVertexLayout);

	void CreatePixelShaderFromFile(ID3D11Device * pd3dDevice
		, const WCHAR* pszFileName
		, LPCSTR pszShaderName
		, LPCSTR pszShaderModel
		, ID3D11PixelShader** ppd3dPixelShader);

public:
	void AddRenderer(shared_ptr<JSRenderer> renderer);
	void AddCamera(shared_ptr<JSCamera> camera);
	void Render();

private:
	unordered_map<ShaderType, ShaderSet*> m_mapShader;
	unordered_map<CenterType, VertexSet*> m_mapVertexBuffer;
	unordered_map<RasterizerType, ID3D11RasterizerState*> m_mapRasterizer;
	unordered_map<SamplerType, ID3D11SamplerState*> m_mapSampler;

	list<shared_ptr<class JSCamera>> m_CameraList;
	unordered_map<RenderLayer, list<shared_ptr<JSRenderer>>> m_mapRenderer;
	ShaderType CurrentShaderType;
	CenterType CurrentCenterType;
	RasterizerType CurrentRasterizerType;
	SamplerType CurrentSamplerType;
};