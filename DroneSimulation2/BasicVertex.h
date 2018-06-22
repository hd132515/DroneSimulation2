#pragma once

#include <d3dx9.h>

struct ColoredVertex
{
	D3DXVECTOR3 pos;
	DWORD color;
};
#define D3DFVF_COLOREDVERT (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct ColoredNormalVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	DWORD color;
};
#define D3DFVF_CNVERT (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)