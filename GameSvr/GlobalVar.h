#pragma once

extern HINSTANCE g_hInst;
extern HWND g_hWnd;

extern INT g_nWindowWidth;
extern INT g_nWindowHeight;

enum {
	LOG_COUNT_MAX = 100,
	LOG_RESERVE_PER_LINE = 30,
};