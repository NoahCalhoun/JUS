#pragma once

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
	ID3D11Device * m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dDeviceContext;

//Function
private:
	HRESULT InitGraphicDevice();
};