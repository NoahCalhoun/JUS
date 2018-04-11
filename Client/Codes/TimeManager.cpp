#include "stdafx.h"
#include "TimeManager.h"

shared_ptr<CTimeManager> CTimeManager::m_pInstance = nullptr;

CTimeManager::CTimeManager()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_PerformanceFrequency))
	{
		m_bHardwareHasPerformanceCounter = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);
		m_fTimeScale = 1.f / m_PerformanceFrequency;
	}
	else
	{
		m_bHardwareHasPerformanceCounter = false;
		m_nLastTime = ::timeGetTime();
		m_fTimeScale = 0.001f;
	}
	m_nSampleCount = 0;
	m_nCurrentFrameRate = 0;
	m_FramePerSecond = 0;
	m_fFpsTimeElapsed = 0.f;
}

CTimeManager::~CTimeManager()
{
}

shared_ptr<CTimeManager> CTimeManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = make_shared<CTimeManager>();
	}
	return m_pInstance;
}

void CTimeManager::Tick(float _fLockFps)
{
	if (m_bHardwareHasPerformanceCounter)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrentTime);
	}
	else
	{
		m_nCurrentTime = ::timeGetTime();
	}

	float fTimeElapsed = (m_nCurrentTime - m_nLastTime) * m_fTimeScale;
	if (_fLockFps > 0.f)
	{
		while (fTimeElapsed < (1.f / _fLockFps))
		{
			if (m_bHardwareHasPerformanceCounter)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrentTime);
			}
			else
			{
				m_nCurrentTime = ::timeGetTime();
			}
			fTimeElapsed = (m_nCurrentTime - m_nLastTime) * m_fTimeScale;
		}
	}

	m_nLastTime = m_nCurrentTime;
	if (fabsf(fTimeElapsed - m_fTimeElapsed) < 1.f)
	{
		memmove(&m_fFrameTime[1], m_fFrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		m_fFrameTime[0] = fTimeElapsed;
		if (m_nSampleCount < MAX_SAMPLE_COUNT)
			m_nSampleCount++;
	}

	m_FramePerSecond++;
	m_fFpsTimeElapsed += fTimeElapsed;
	if (m_fFpsTimeElapsed > 1.f)
	{
		m_nCurrentFrameRate = m_FramePerSecond;
		m_FramePerSecond = 0;
		m_fFpsTimeElapsed = 0.f;
	}

	m_fTimeElapsed = 0.f;
	for (ULONG i = 0; i < m_nSampleCount; ++i)
	{
		m_fTimeElapsed += m_fFrameTime[i];
	}
	if (m_nSampleCount > 0)
		m_fTimeElapsed /= m_nSampleCount;
}

unsigned long CTimeManager::GetFrameRate(LPTSTR _lpszString, int _nCharacters)
{
	if (_lpszString)
	{
		_itow_s(m_nCurrentFrameRate, _lpszString, _nCharacters, 10);
		wcscat_s(_lpszString, _nCharacters, _T(" FPS"));
	}
	return m_nCurrentFrameRate;
}

float CTimeManager::GetTimeElaped()
{
	return m_fTimeElapsed;
}
