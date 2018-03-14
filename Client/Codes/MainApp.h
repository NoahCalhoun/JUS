#pragma once

#include "GraphicDevice.h"
#include "InputDevice.h"

class CMainApp
{
public:
	explicit CMainApp();
	virtual ~CMainApp();

private:
	shared_ptr<CGraphicDevice> m_pGraphicDev;
	shared_ptr<CInputDevice> m_pInputDev;

public:
	void InitDevice();
	void UpdateApplication();
	void ReleaseApplication();
};