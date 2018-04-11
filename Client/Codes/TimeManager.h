#pragma once

#include "Define.h"

const ULONG MAX_SAMPLE_COUNT = 50;

class CTimeManager
{
public:
	explicit CTimeManager();
	virtual ~CTimeManager();

private:
	static shared_ptr<CTimeManager> m_pInstance;
public:
	static shared_ptr<CTimeManager> GetInstance();

//Field
private:
	bool m_bHardwareHasPerformanceCounter;
	float m_fTimeScale;
	float m_fTimeElapsed;
	__int64 m_nCurrentTime;
	__int64 m_nLastTime;
	__int64 m_PerformanceFrequency;

	float m_fFrameTime[MAX_SAMPLE_COUNT];
	ULONG m_nSampleCount;

	unsigned long m_nCurrentFrameRate;
	unsigned long m_FramePerSecond;
	float m_fFpsTimeElapsed;

//Function
public:
	void Tick(float _fLockFps = 0.f);
	unsigned long GetFrameRate(LPTSTR _lpszString = NULL, int _nCharacters = 0);
	float GetTimeElaped();
};