#pragma once

#include <d3dx9.h>

class Geometry
{
public:
	Geometry();
	virtual ~Geometry();
private:
protected:
	IDirect3DVertexBuffer9* pVB;
	IDirect3DIndexBuffer9* pIB;
public:

public:
	virtual int prepare(IDirect3DDevice9* pDev) = 0;
	virtual int render(IDirect3DDevice9* pDev) = 0;

	void release();
};