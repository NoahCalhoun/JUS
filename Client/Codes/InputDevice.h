#pragma once

#include "Define.h"

class CInputDevice
{
public:
	explicit CInputDevice();
	virtual ~CInputDevice();

private:
	static shared_ptr<CInputDevice> m_pInstance;
public:
	static shared_ptr<CInputDevice> GetInstance();

public:
	void UpdateDevice();

	void OnProcessMouseMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessKeyboardMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT OnProcessWindowMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
};