#pragma once

#include <d3dx9.h>

class Box
{
public:
	Box();
	~Box();
private:
	D3DMATERIAL9 material;
	IDirect3DVertexBuffer9* pVB;
protected:
public:
	int prepare(IDirect3DDevice9* pDev);
	int render(IDirect3DDevice9* pDev);
	void release();
};