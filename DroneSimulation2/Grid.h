#pragma once

#include <d3dx9.h>
#include "BasicVertex.h"

class Grid
{
public:
	Grid(int _size, int _unit);
	~Grid();
private:
	int size, unit;
	IDirect3DVertexBuffer9* pVB;
protected:
public:
	int prepare(IDirect3DDevice9* pDev);
	int render(IDirect3DDevice9* pDev);
	void release();
};