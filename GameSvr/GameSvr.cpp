// GameSvr.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameSvr.h"

#include <CommCtrl.h>
#include "Log.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	g_hAntiMultiClientMutex = CreateMutex(NULL, FALSE, _T("MyApp"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox(NULL, _T("이미 실행중입니다."), _T("알림"), MB_OK);
		return 0;
	}

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GAMESVR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//g_pLog = make_shared<CLog>();
	//g_pLog->Initialize();
	CLog hil;
	hil.Initialize();

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMESVR));

	MSG msg;

	LOCK lockii;
	shared_ptr<int> ii = make_shared<int>(3);

	BOOL bT1 = TRUE, bT2 = TRUE, bT3 = TRUE;
	BOOL bT4 = TRUE, bT5 = TRUE, bT6 = TRUE;

	auto func = [&lockii, &hil, &ii](BOOL* b, INT _i) {
		INT i = 0;
		while (*b) {
			Sleep(1);
			if (LOCK_GUARD(lockii); ii) {
				*ii += 1;
				hil.AddLog((LOGTYPE)_i, _T("쓰레드 ID : ") + TO_STRING(_i) + _T(" / 호출된 횟수 : ") + TO_STRING(++i) + _T(" / 쓰레드 총 호출 횟수 : ") + TO_STRING(*ii));
			}
		}
	};

	SYSTEM_INFO info;
	GetSystemInfo(&info);

	enum {ARRAY_COUNT = 15,};
	BOOL bTTrigger[ARRAY_COUNT];
	thread thTemps[ARRAY_COUNT];
	for (INT i = 0; i < ARRAY_COUNT; i++)
	{
		bTTrigger[i] = TRUE;
		thTemps[i] = thread(func, &bTTrigger[i], i);
	}

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (GetAsyncKeyState(VK_RETURN)) {
			//g_pLog->AddLog(to_wstring(i++) + _T("ㄹㄹㄹㄹㄹㄹㄹㄹㄹasdfasdfㄴㅇㄹㄴㅇㄹㄴㅇㄹㅇㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹㅎㅎㅎㅎㅎㅎㅎㅎㅎㅎㄹㄹㄹㄹㄹㄹㄹㄹㄹㄹ"));
		}
	}

	for (size_t i = 0; i < ARRAY_COUNT; i++)
	{
		bTTrigger[i] = FALSE;
	}
	for (size_t i = 0; i < ARRAY_COUNT; i++)
	{
		if (thTemps[i].joinable()) thTemps[i].join();
	}

	ReleaseMutex(g_hAntiMultiClientMutex);
	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMESVR));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GAMESVR);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindowW(szWindowClass, szTitle,
		WS_SYSMENU | WS_BORDER | WS_DLGFRAME | WS_MINIMIZEBOX,
		0, 0, g_nWindowWidth, g_nWindowHeight, nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NOTIFY:
	{
		switch (((LPNMLISTVIEW)lParam)->hdr.code)
		{
		case LVN_ITEMCHANGED:
			INT i = 0;

			break;

		}
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
