#include "stdafx.h"
#include "InputDevice.h"

#include "GraphicDevice.h"

shared_ptr<CInputDevice> CInputDevice::m_pInstance = nullptr;

CInputDevice::CInputDevice()
{

}

CInputDevice::~CInputDevice()
{

}

shared_ptr<CInputDevice> CInputDevice::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = make_shared<CInputDevice>();
	}

	return m_pInstance;
}

void CInputDevice::UpdateDevice()
{
}

void CInputDevice::OnProcessMouseMessage(UINT _nMessageID, WPARAM _wParam, LPARAM _lParam)
{
	switch (_nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:
		break;

	default:
		break;
	}
}

void CInputDevice::OnProcessKeyboardMessage(UINT _nMessageID, WPARAM _wParam, LPARAM _lParam)
{
	switch (_nMessageID)
	{
	case WM_KEYUP:
		switch (_wParam)
		{
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

LRESULT CALLBACK CInputDevice::OnProcessWindowMessage(UINT _nMessageID, WPARAM _wParam, LPARAM _lParam)
{
	switch (_nMessageID)
	{
	case WM_SIZE:
	{
		auto graphicDev = CGraphicDevice::GetInstance();
		graphicDev->RenewDeviceSize(LOWORD(_lParam), HIWORD(_lParam));
		graphicDev->CreateRenderTargetView();
		graphicDev->SetViewport();
	}
	break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessMouseMessage(_nMessageID, _wParam, _lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessKeyboardMessage(_nMessageID, _wParam, _lParam);
		break;

	default:
		break;
	}

	return 0;
}
