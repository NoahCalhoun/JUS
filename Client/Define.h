#pragma once

//Global
extern HWND g_hWnd;
extern HINSTANCE g_hInst;

//Define
#define CLIENT_WINDOW_WIDTH 640
#define CLIENT_WINDOW_HEIGHT 480

#define D3DCOLOR_ARGB(a,r,g,b) ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff<<16)|(((g)&0xff<<8)|(((b)&0xff)))
#define D3DCOLOR_XRGB(r,g,b) D3DCOLOR_ARGB(0xff,r,g,b)
#define D3DCOLOR_COLORVALUE(r,g,b,a) D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))

#define VS_SLOT_VIEWPROJECTION_MATRIX 0x00
#define VS_SLOT_WORLD_MATRIX 0x01