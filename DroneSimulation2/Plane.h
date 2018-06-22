#pragma once

#include <d3dx9.h>

class Plane
{
public:
	Plane(int _cell, float _unit);
	~Plane();
private:
	int cell;
	float unit;
	IDirect3DVertexBuffer9* pVB;
	IDirect3DIndexBuffer9* pIB;

	D3DMATERIAL9 material;
protected:
public:
	int prepare(IDirect3DDevice9* pDev);
	int render(IDirect3DDevice9* pDev);
	void release();
};