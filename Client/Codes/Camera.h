#pragma once

#include "JSObjectBase.hpp"
#include "RenderManager.h"

struct VS_CB_VIEWPROJECTION_MATRIX
{
	JSMATRIX View;
	JSMATRIX Project;
};

class JSCamera : public JSComponentBase
{
protected:
	explicit JSCamera();
public:
	virtual ~JSCamera();

public:
	static EComponentType GetType() { return EComponentType::Camera; }
	static shared_ptr<JSCamera> Create();
	virtual void InitComponent() override;
	virtual void UpdateComponent() override;

	void SetViewport(DWORD _xTopLeft, DWORD _yTopLeft, DWORD _width, DWORD _height, float _minZ, float _maxZ);
	void SetProjection(bool _perspective, float _near, float _far, float _aspect_width, float _fov_height);
	void AddLayer(RenderLayer layer);
	void GenerateView();
	void GenerateProject();
	
	void CreateShaderVariables();
	void UpdateShaderVariables();
	bool HasLayer(RenderLayer layer);

private:
	shared_ptr<class JSTransform> m_pTransform;
	bool m_bPerspective;
	float m_fNear;
	float m_fFar;
	union
	{
		struct Perspective
		{
			float fAspectRatio;
			float fFOV;
		};

		struct Orthogonal
		{
			float fWidth;
			float fHeight;
		};

		Perspective m_tPerspective;
		Orthogonal m_tOrthogonal;
	};

	INT8 Layer;
	int m_iDepth;
	JSMATRIX m_matView;
	JSMATRIX m_matProject;
	D3D11_VIEWPORT m_tViewport;
	ID3D11Buffer* m_pVeiwProjConstBuffer;
	
public:
	bool operator<(const JSCamera& other)
	{
		if (m_iDepth < other.m_iDepth)
			return true;
		else
			return false;
	};
};