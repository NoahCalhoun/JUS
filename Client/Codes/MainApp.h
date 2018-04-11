#pragma once

#include "GraphicDevice.h"
#include "InputDevice.h"
#include "TimeManager.h"

#include "TestScene.h"

class CMainApp
{
public:
	explicit CMainApp();
	virtual ~CMainApp();

private:
	shared_ptr<CGraphicDevice> m_pGraphicDev;
	shared_ptr<CInputDevice> m_pInputDev;
	shared_ptr<CTimeManager> m_pTimeMgr;

	shared_ptr<CTestScene> m_pScene;

	_TCHAR m_pszBuffer[50];

public:
	void InitDevice();
	void UpdateApplication();
	void ReleaseApplication();
};