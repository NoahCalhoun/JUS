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
#define PS_SLOT_TEXTURE 0x00
#define PS_SLOT_SAMPLER 0x00

struct JSVECTOR : public XMVECTORF32
{
	JSVECTOR() { f[0] = 0; f[1] = 0; f[2] = 0; f[3] = 0; }
	JSVECTOR(float x, float y, float z)
	{
		f[0] = x;
		f[1] = y;
		f[2] = z;
		f[3] = 1;
	}

	float x() { return f[0]; }
	float y() { return f[1]; }
	float z() { return f[2]; }
	float w() { return f[3]; }

	JSVECTOR& operator= (XMVECTOR V) { this->v = V; return *this; }

	JSVECTOR    operator+ () { JSVECTOR value = (*this); return value; }
	JSVECTOR    operator- () { JSVECTOR value = (*this) * -1; return value; }

	JSVECTOR&   operator+= (JSVECTOR V) { this->v = this->v + V.v; return *this; }
	JSVECTOR&   operator-= (JSVECTOR V) { this->v = this->v - V.v; return *this; }
	JSVECTOR&   operator*= (JSVECTOR V) { this->v = this->v * V.v; return *this; }
	JSVECTOR&   operator/= (JSVECTOR V) { this->v = this->v / V.v; return *this; }
	JSVECTOR&   operator*= (FLOAT S) { this->v = this->v * S; return *this; }
	JSVECTOR&   operator/= (FLOAT S) { this->v = this->v / S; return *this; }

	JSVECTOR    operator+ (JSVECTOR V) { JSVECTOR value = (*this) + V; return value; }
	JSVECTOR    operator- (JSVECTOR V) { JSVECTOR value = (*this) - V; return value; }
	JSVECTOR    operator* (JSVECTOR V) { JSVECTOR value = (*this) * V; return value; }
	JSVECTOR    operator/ (JSVECTOR V) { JSVECTOR value = (*this) / V; return value; }
	JSVECTOR    operator* (FLOAT S) { JSVECTOR value = (*this) * S; return value; }
	JSVECTOR    operator/ (FLOAT S) { JSVECTOR value = (*this) / S; return value; }

	static const JSVECTOR Zero() { return JSVECTOR(0, 0, 0); }
	static const JSVECTOR One() { return JSVECTOR(1, 1, 1); }
};

JSVECTOR operator* (FLOAT S, JSVECTOR V) { JSVECTOR value = V * S; return value; }

struct JSMATRIX : public XMMATRIX
{
	JSMATRIX() {}

	JSMATRIX(float _00, float _01, float _02, float _03
		, float _10, float _11, float _12, float _13
		, float _20, float _21, float _22, float _23
		, float _30, float _31, float _32, float _33)
		: XMMATRIX(_00, _01, _02, _03
			, _10, _11, _12, _13
			, _20, _21, _22, _23
			, _30, _31, _32, _33)
	{

	}

	JSMATRIX(XMMATRIX M) : XMMATRIX(M) { }

	JSMATRIX& operator= (CONST XMMATRIX M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = M._14;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = M._24;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = M._34;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = M._44;
		return *this;
	}

	JSMATRIX& operator*= (CONST _XMMATRIX& M) { (*this) = (*this) * M; return *this; }
	JSMATRIX operator* (CONST _XMMATRIX& M) CONST
	{
		_XMMATRIX mat(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44);
		return JSMATRIX(mat * M);
	}

	static const JSMATRIX Identity() { return JSMATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); }
};