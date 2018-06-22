#pragma once

#include "Node.h"
#include "BasicVertex.h"

class GridGeometry : public Geometry
{
public:
	GridGeometry(int _size, int _unit);
	~GridGeometry();
private:
	int size, unit;
protected:
public:
	virtual int prepare(IDirect3DDevice9* pDev);
	virtual int render(IDirect3DDevice9* pDev);
};

class Grid : public SceneNode
{
public:
	Grid();
	virtual ~Grid();
private:
protected:
public:
	int prepare(IDirect3DDevice9* pDev);
};