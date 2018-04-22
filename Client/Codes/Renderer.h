#pragma once

#include "JSObjectBase.hpp"
#include "RenderManager.h"

class JSRenderer : public JSComponentBase
{
protected:
	explicit JSRenderer();
public:
	virtual ~JSRenderer();

	static EComponentType GetType() { return EComponentType::Renderer; }
	static shared_ptr<JSRenderer> Create();
	virtual void InitComponent() override;
	virtual void UpdateComponent() override;

	void SetLayer(RenderLayer layer);
	void SetRenderType(ShaderType shader, CenterType center, RasterizerType rasterizer, SamplerType sampler);

	void Render();

	RenderLayer m_eRenderLayer;
	ShaderType m_eShaderType;
	CenterType m_eCenterType;
	RasterizerType m_eRasterizerType;
	SamplerType m_eSamplerType;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11ShaderResourceView* m_pResourceView;
	shared_ptr<class JSTransform> m_pTransform;
};