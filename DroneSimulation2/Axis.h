#pragma once

#include <d3dx9.h>

class Axis
{
public:
	Axis();
	~Axis();
private:
	IDirect3DVertexBuffer9* pVB;
public:
	//<returns>
	// 0 : succeeded
	// -1 : failed to create vertex buffer
	// -2 : failed to lock vertex buffer
	// -3 : failed to unlock vertex buffer
	int prepare(IDirect3DDevice9* pDev);

	//<returns>
	// 0 : succeeded
	// -1 : failed to call draw primitive
	int render(IDirect3DDevice9* pDev);

	void release();
};