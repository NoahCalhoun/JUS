#pragma once

class CMainApp
{
public:
	explicit CMainApp();
	virtual ~CMainApp();

private:
	shared_ptr<class CGraphicDevice> m_pGraphicDev;
	shared_ptr<class CInputDevice> m_pInputDev;
	shared_ptr<class CTimeManager> m_pTimeMgr;
	shared_ptr<class JSRenderManager> m_pRenderManager;

	shared_ptr<class JSObjectBase> m_pCamera;
	shared_ptr<class JSObjectBase> m_pObject;

	_TCHAR m_pszBuffer[50];

public:
	void InitDevice();
	void UpdateApplication();
	void ReleaseApplication();
};