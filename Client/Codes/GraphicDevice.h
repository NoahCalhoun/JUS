#pragma once

#include "Define.h"

class CGraphicDevice
{
public:
	explicit CGraphicDevice();
	virtual ~CGraphicDevice();

private:
	static shared_ptr<CGraphicDevice> mInstance;
public:
	static shared_ptr<CGraphicDevice> GetInstance();

//Field
private:
	ID3D11Device* m_pd3dDevice;						//리소스 생성
	IDXGISwapChain* m_pDXGISwapChain;				//디스플레이 제어
	ID3D11DeviceContext* m_pd3dDeviceContext;		//파이프라인 설정
	ID3D11RenderTargetView* m_pd3dRenderTargetView;	//렌더 타겟 뷰

	int m_iClientWindowWidth;
	int m_iClientWindowHeight;

//Function
private:
	HRESULT InitGraphicDevice();
};