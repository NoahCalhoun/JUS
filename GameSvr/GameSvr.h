#pragma once

#include "resource.h"

#define MAX_LOADSTRING 100

class CLog;
shared_ptr<CLog> g_pLog = NULL;

thread::id g_tidMain;

HANDLE g_hAntiMultiClientMutex;

WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);